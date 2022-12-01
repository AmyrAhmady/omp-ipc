#include "Socket.hpp"
#include "Handler.hpp"
#include <nng/supplemental/util/platform.h>

std::vector<MessageSocket*> MessageSocket::sockets;
// SafeQueue<MessageData> MessageSocket::messageQueue;

MessageSocket::MessageSocket(const std::string& name)
{
	int ret_value = 0;

	ret_value = nng_rep0_open(&socket_);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_rep0_open: " << nng_strerror(ret_value);
		std::exit(1);
	}

	ret_value = nng_listen(socket_, (std::string("ipc:///tmp/") + name + ".ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_listen: " << nng_strerror(ret_value);
		std::exit(1);
	}

	thread_ = std::thread(&MessageSocket::Process, this);
}

MessageSocket::~MessageSocket()
{
	stopReceiveProcess_ = true;
	thread_.join();
	nng_close(socket_);
}

//void MessageSocket::ProcessQueue()
//{
//	while (true)
//	{
//		MessageData message;
//		bool available = messageQueue.dequeue(message);
//		if (available)
//		{
//			nlohmann::json returnObject = MessageHandler::Call(message.name, message.params);
//			message.sender->Send(returnObject.dump());
//			continue;
//		}
//		else
//		{
//			break;
//		}
//	}
//}

bool MessageSocket::Receive(std::string& message)
{
	char* buf = NULL;
	size_t sz = 0;
	int ret_value = 0;

	ret_value = nng_recv(socket_, &buf, &sz, NNG_FLAG_ALLOC | NNG_FLAG_NONBLOCK);
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

void MessageSocket::Send(const std::string& message)
{
	int ret_value = 0;

	ret_value = nng_send(socket_, static_cast<void*>(const_cast<char*>(message.data())), message.size(), 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_send: " << nng_strerror(ret_value);
		std::exit(1);
	}
}

void MessageSocket::Process()
{
	for (;;)
	{
		if (stopReceiveProcess_) break;

		std::string recvBuf;
		bool hasReceived = Receive(recvBuf);
		if (hasReceived)
		{
			nlohmann::json messageObject = nlohmann::json::parse(recvBuf);
			if (messageObject.count("name"))
			{
				nlohmann::json returnObject =
					MessageHandlerPool::Get()->Call(messageObject["name"].get<std::string>(), messageObject["params"]);
				Send(returnObject.dump());
			}
		}

		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	}
}
