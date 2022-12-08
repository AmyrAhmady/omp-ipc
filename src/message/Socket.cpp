#include "Socket.hpp"
#include "Handler.hpp"
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>

std::vector<MessageSocket*> MessageSocket::sockets;

MessageSocket::MessageSocket(const std::string& name)
	: socketName_(name)
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

	thread_ = std::thread(&MessageSocket::Tick, this);
}

MessageSocket::~MessageSocket()
{
	stopReceiveProcess_ = true;
	thread_.join();
	nng_close(socketServer_);
	nng_close(socketClient_);
}

void MessageSocket::ProcessEvent(const std::string& name, const nlohmann::json& args)
{
	for (auto socket : MessageSocket::sockets)
	{
		// Set this to true so our custom worker thread doesn't process anything while we are in an event scope
		// Worker's loop is placed in MessageSocket::Tick
		socket->processingEvents_ = true;

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

		// Set this back to false so our worker's thread can continue processing standalone messages
		socket->processingEvents_ = false;
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

void MessageSocket::ProcessRequest()
{
	std::string recvBuf;
	bool hasReceived = ReceiveRequest(recvBuf);
	if (hasReceived)
	{
		nlohmann::json messageObject = nlohmann::json::parse(recvBuf);
		if (messageObject.count("name"))
		{
			nlohmann::json returnObject =
				MessageHandlerPool::Get()->Call(messageObject["name"].get<std::string>(), messageObject["params"], this);
			SendResponse(returnObject.dump());
		}
		else
		{
			SendResponse("{\"ret_value\":\"invalid_format\"}");
		}
	}
}

void MessageSocket::Tick()
{
	for (;;)
	{
		if (stopReceiveProcess_) break;
		// Skip processing standalone requests, when set to true it means we are processing events and requests in their scopes
		if (processingEvents_) continue;
		ProcessRequest();
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	}
}
