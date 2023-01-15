#include "Socket.hpp"
#include "Handler.hpp"
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

std::vector<MessageSocket*> MessageSocket::sockets;

MessageSocket::MessageSocket(const std::string& name)
	: socketName_(name), socketClient_({ 0 }), socketServer_({ 0 }), clientInitialized_(false)
{
	int ret_value = 0;

	ret_value = nng_rep0_open(&socketServer_);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_rep0_open: " << nng_strerror(ret_value);
		std::exit(1);
	}

	ret_value = nng_listen(socketServer_, (std::string("ipc:///tmp/") + name + "_server.ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_listen: " << nng_strerror(ret_value);
		std::exit(1);
	}
}

MessageSocket::~MessageSocket()
{
	nng_close(socketServer_);
	nng_close(socketClient_);
}

void MessageSocket::ProcessEvent(const std::string& name, const nlohmann::json& args)
{
	for (auto socket : MessageSocket::sockets)
	{
		// Check if event is subscribed
		if (!socket->IsEventSubscribed(name))
		{
			continue;
		}

		// Send a request to client to allow event processing and wait for `event_end` response so we know when to stop processing
		nlohmann::json eventData;
		eventData["name"] = "event";
		eventData["params"]["event"] = name;
		eventData["params"]["args"] = args;
		socket->SendRequest(eventData.dump());

		while (true)
		{
			std::string recvBuff;
			auto receivedResponse = socket->ReceiveResponse(recvBuff);
			if (!receivedResponse)
			{
				socket->ProcessRequest();
				continue;
			}

			nlohmann::json recvObject = nlohmann::json::parse(recvBuff);
			if (recvObject.count("name"))
			{
				std::string actionName = recvObject["name"].get<std::string>();
				if (actionName == "event_end")
				{
					break;
				}
			}
		}
	}
}

void MessageSocket::ProcessRequests(Microseconds elapsed, TimePoint now)
{
	for (auto socket : MessageSocket::sockets)
	{
		// Try to receive requests sent by client, as if client is trying to call an IPC api
		// After N tries (N could be any number, maybe even configurable) if there are not requests, we will process them (if there are any) in next tick
		// Or in the middle of event processings
		// Note: These type of calls are outside of event scopes, like global scope, timers, threads, or callbacks
		// For example in JS, in connection successful callback of database conneciton attempts, or setTimeout/setInterval

		int failedReadAttempts = 0;
		while (true)
		{
			if (socket->ProcessRequest())
			{
				failedReadAttempts = 0;
			}
			else
			{
				failedReadAttempts++;
			}

			// If amount of failed read/receive attempts wen't over 5 (or equal) just let next tick process queued up requests
			// This can also be result of empty queue of requests, but we need to make sure I guess?
			if (failedReadAttempts >= 5)
			{
				break;
			}
		}
	}
}

void MessageSocket::CreateClient()
{
	int ret_value = 0;

	ret_value = nng_req0_open(&socketClient_);
	if (ret_value != 0)
	{
		std::cout << "[MessageSocket::CreateClient Fatal Error] nng_req0_open: " << nng_strerror(ret_value);
		std::exit(1);
	}

	ret_value = nng_dial(socketClient_, (std::string("ipc:///tmp/") + socketName_ + "_client.ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[MessageSocket::CreateClient Fatal Error] nng_dial: " << nng_strerror(ret_value);
		std::exit(1);
	}

	clientInitialized_ = true;
}

void MessageSocket::DestroyClient()
{
	clientInitialized_ = false;
	nng_close(socketClient_);
}

bool MessageSocket::ReceiveRequest(std::string& message)
{
	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketServer_, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		std::exit(1);
		return false;
	}

	message = std::string(buf, sz);
	return true;
}

void MessageSocket::SendResponse(const std::string& message)
{
	int ret_value = 0;

	ret_value = nng_send(socketServer_, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_send: " << nng_strerror(ret_value);
		//std::exit(1);
	}
}

bool MessageSocket::ReceiveResponse(std::string& message)
{
	if (!clientInitialized_)
	{
		return false;
	}

	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socketClient_, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK);
	if (ret_value == NNG_EAGAIN)
	{
		return false;
	}

	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_recv: " << nng_strerror(ret_value);
		return false;
	}

	message = std::string(buf, sz);
	return true;
}

void MessageSocket::SendRequest(const std::string& message)
{
	if (!clientInitialized_)
	{
		return;
	}

	int ret_value = 0;

	ret_value = nng_send(socketClient_, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_send: " << nng_strerror(ret_value);
		//std::exit(1);
	}
}

bool MessageSocket::ProcessRequest()
{
	std::string recvBuf;
	bool hasReceived = ReceiveRequest(recvBuf);
	if (hasReceived)
	{
		try {
			nlohmann::json messageObject = nlohmann::json::parse(recvBuf);
			if (messageObject.count("name"))
			{
				std::cout << "params: " << messageObject.dump() << std::endl;
				nlohmann::json returnObject =
					MessageHandlerPool::Get()->Call(messageObject["name"].get<std::string>(), messageObject["params"], this);
				SendResponse(returnObject.dump());
			}
			else
			{
				SendResponse("{\"ret_value\":\"invalid_format\"}");
			}
		}
		catch (std::exception e) {
			std::cout << "[Exception] MessageSocket::ProcessRequest: " << e.what() << std::endl;
		}
		return true;
	}
	return false;
}
