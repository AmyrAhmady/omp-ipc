#include <cstdlib>
#include <iostream>
#include <nng/nng.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include <robin_hood.h>

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

	MessageSocket(const std::string& name);
	~MessageSocket();

	// Process events in each tick, send request to each socket and wait for their return response
	static void ProcessEvent(const std::string& name, const nlohmann::json& args);

	// Process message requests in socket's own thread in a loop
	void Tick();

	// Receive request, process it, and send response back to client
	void ProcessRequest();

	// Send a response back to requester, after receiving their request
	void SendResponse(const std::string& message);

	// Try to receive queued requests sent from clients, to process and send them a response back
	bool ReceiveRequest(std::string& message);

	// Send a request to a client, like asking to fire events
	void SendRequest(const std::string& message);

	// Receive response after sending a client requests, like event return values
	bool ReceiveResponse(std::string& message);

	// Create an IPC client, so we can request something from clients and get a response
	void CreateClient();

	// Destroy the IPC client
	void DestroyClient();

	// Check if client is initialized
	bool IsClientInitialized() { return clientInitialized_; }

	// Add event name to list of subscribed events
	void SubscribeToEvent(const std::string& eventName)
	{
		if (!IsEventSubscribed(eventName))
		{
			subscribedEventNames.insert(eventName);
		}
	}

	// Remove event name from list of subscribed events
	void UnsubscribeToEvent(const std::string& eventName)
	{
		if (IsEventSubscribed(eventName))
		{
			subscribedEventNames.erase(eventName);
		}
	}

	// Is event name available in subscribed event name list
	bool IsEventSubscribed(const std::string& eventName)
	{
		auto it = subscribedEventNames.find(eventName);
		if (it == subscribedEventNames.cend())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool processingEvents_ = false;
private:
	nng_socket socketServer_;
	nng_socket socketClient_;
	std::string socketName_;
	std::thread thread_;
	robin_hood::unordered_flat_set<std::string> subscribedEventNames;
	bool stopReceiveProcess_ = false;
	bool clientInitialized_ = false;
};
