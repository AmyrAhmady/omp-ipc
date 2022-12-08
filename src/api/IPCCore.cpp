#include "../message/Handler.hpp"
#include "../message/Socket.hpp"

IPC_API_EX(create_omp_ipc_client, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (!messageSocket->IsClientInitialized())
	{
		messageSocket->CreateClient();
		return "{\"ret_value\":true}"_json;
	}
	else
	{
		messageSocket->DestroyClient();
		messageSocket->CreateClient();
		return "{\"ret_value\":true}"_json;
	}
}

IPC_API_EX(subscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->SubscribeToEvent(params["eventName"].get<std::string>());
		return "{\"ret_value\":true}"_json;
	}
	return "{\"ret_value\":false}"_json;
}

IPC_API_EX(unsubscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->SubscribeToEvent(params["eventName"].get<std::string>());
		return "{\"ret_value\":true}"_json;
	}
	return "{\"ret_value\":false}"_json;
}
