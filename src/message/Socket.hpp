#include <cstdlib>
#include <iostream>
#include <nng/nng.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <chrono>

class MessageSocket;

struct MessageData
{
	std::string name;
	nlohmann::json params;
	MessageSocket* sender;
};

class MessageSocket
{
public:
	struct IPCWorker
	{
		enum class STATE
		{
			INIT,
			RECV,
			WAIT,
			SEND
		} state;
		nng_aio* aio;
		nng_msg* msg;
		nng_ctx  ctx;
		MessageSocket* messageSocket;
	};

	static std::vector<MessageSocket*> sockets;
	// static SafeQueue<MessageData> messageQueue;

	MessageSocket(const std::string& name);
	~MessageSocket();

	static void ProcessQueue();

	IPCWorker* AllocWorker();
	static void Process(IPCWorker* worker);

private:
	nng_socket socket_;
	std::thread thread_;
	bool stopReceiveProcess_ = false;
};
