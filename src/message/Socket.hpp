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

	void Tick();
	void ProcessRequest();
	void CreateClient();

	void SendResponse(const std::string& message);
	bool ReceiveRequest(std::string& message);

	void SendRequest(const std::string& message);
	bool ReceiveResponse(std::string& message);

	bool processingEvents_ = false;
private:
	nng_socket socketServer_;
	nng_socket socketClient_;
	std::string socketName_;
	std::thread thread_;
	bool stopReceiveProcess_ = false;
	bool clientInitialized_ = false;
};
