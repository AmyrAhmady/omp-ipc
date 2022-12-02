#include "Socket.hpp"
#include "Handler.hpp"
#include <nng/supplemental/util/platform.h>
#include <nng/nng.h>

std::vector<MessageSocket*> MessageSocket::sockets;
// SafeQueue<MessageData> MessageSocket::messageQueue;

#ifndef PARALLEL
#define PARALLEL 20
#endif

MessageSocket::IPCWorker* workers[PARALLEL];

MessageSocket::MessageSocket(const std::string& name)
{
	int ret_value = 0;

	ret_value = nng_rep0_open(&socket_);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_rep0_open: " << nng_strerror(ret_value) << std::endl;
		std::exit(1);
	}

	for (int i = 0; i < PARALLEL; i++) {
		workers[i] = reinterpret_cast<MessageSocket::IPCWorker*>(AllocWorker());
	}

	ret_value = nng_listen(socket_, (std::string("ipc:///tmp/") + name + ".ipc").c_str(), NULL, 0);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_listen: " << nng_strerror(ret_value) << std::endl;
		std::exit(1);
	}

	for (int i = 0; i < PARALLEL; i++) {
		MessageSocket::Process(workers[i]); // this starts them going (INIT state)
	}

	/*
	for (;;) {
		nng_msleep(3600000); // neither pause() nor sleep() portable
	}
	*/

	//thread_ = std::thread(&MessageSocket::Process, this);
}

MessageSocket::~MessageSocket()
{
	stopReceiveProcess_ = true;
	thread_.join();
	nng_close(socket_);
}

MessageSocket::IPCWorker* MessageSocket::AllocWorker()
{
	MessageSocket::IPCWorker* worker;
	int ret_value;

	worker = static_cast<MessageSocket::IPCWorker*>(nng_alloc(sizeof(*worker)));
	if (worker == NULL)
	{
		std::cout << "[Fatal Error] nng_alloc: " << nng_strerror(NNG_ENOMEM) << std::endl;
		std::exit(1);
	}

	ret_value = nng_aio_alloc(&worker->aio, (void(*)(void*))(MessageSocket::Process), worker);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_aio_alloc: " << nng_strerror(ret_value) << std::endl;
		std::exit(1);
	}

	ret_value = nng_ctx_open(&worker->ctx, socket_);
	if (ret_value != 0)
	{
		std::cout << "[Fatal Error] nng_ctx_open: " << nng_strerror(ret_value) << std::endl;
		std::exit(1);
	}

	worker->state = MessageSocket::IPCWorker::STATE::INIT;
	worker->messageSocket = this;
	return worker;
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

void MessageSocket::Process(MessageSocket::IPCWorker* worker)
{
	nng_msg* msg;
	int ret_value;

	switch (worker->state)
	{
	case IPCWorker::STATE::INIT:
		worker->state = IPCWorker::STATE::RECV;
		nng_ctx_recv(worker->ctx, worker->aio);
		break;
	case IPCWorker::STATE::RECV:
	{
		ret_value = nng_aio_result(worker->aio);
		if (ret_value != 0)
		{
			std::cout << "[Fatal Error] nng_ctx_recv: " << nng_strerror(ret_value) << std::endl;
			std::exit(1);
		}

		msg = nng_aio_get_msg(worker->aio);
		char* body = static_cast<char*>(nng_msg_body(msg));
		int len = nng_msg_len(msg);
		if (len < 1)
		{
			nng_msg_free(msg);
			nng_ctx_recv(worker->ctx, worker->aio);
			return;
		}

		worker->msg = msg;

		std::string recvBuf(reinterpret_cast<char*>(body), len);
		nlohmann::json messageObject = nlohmann::json::parse(recvBuf);
		if (messageObject.count("name"))
		{
			nlohmann::json returnObject =
				MessageHandlerPool::Get()->Call(messageObject["name"].get<std::string>(), messageObject["params"]);

			nng_msg_free(worker->msg);
			nng_msg_alloc(&worker->msg, 0);
			nng_msg_append(worker->msg, returnObject.dump().c_str(), returnObject.dump().size());
		}
		else
		{
			nlohmann::json returnObject = "{\"ret_value\":\"invalid_format\"}"_json;
			nng_msg_free(worker->msg);
			nng_msg_alloc(&worker->msg, 0);
			nng_msg_append(worker->msg, returnObject.dump().c_str(), returnObject.dump().size());
		}

		worker->state = IPCWorker::STATE::WAIT;
		nng_sleep_aio(0, worker->aio);
		break;
	}
	case IPCWorker::STATE::WAIT:
		// We could add more data to the message here.
		nng_aio_set_msg(worker->aio, worker->msg);
		worker->state = IPCWorker::STATE::SEND;
		nng_ctx_send(worker->ctx, worker->aio);
		break;
	case IPCWorker::STATE::SEND:
		ret_value = nng_aio_result(worker->aio);
		if (ret_value != 0)
		{
			nng_msg_free(worker->msg);
			std::cout << "[Fatal Error] nng_ctx_send: " << nng_strerror(ret_value) << std::endl;
			std::exit(1);
		}
		worker->state = IPCWorker::STATE::RECV;
		nng_ctx_recv(worker->ctx, worker->aio);
		break;
	default:
		std::cout << "[Fatal Error] bad state!: " << nng_strerror(NNG_ESTATE) << std::endl;
		std::exit(1);
		break;
	}
	/*
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
	*/
}
