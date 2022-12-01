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
	static std::vector<MessageSocket*> sockets;
	// static SafeQueue<MessageData> messageQueue;

	MessageSocket(const std::string& name);
	~MessageSocket();

	static void ProcessQueue();

	void Process();
	void Send(const std::string& message);
	bool Receive(std::string& message);

private:
	nng_socket socket_;
	std::thread thread_;
	bool stopReceiveProcess_ = false;
};
