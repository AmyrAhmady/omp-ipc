#include "../message/Handler.hpp"
#include "../message/Socket.hpp"

IPC_API_EX(create_omp_ipc_client, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (!messageSocket->IsClientInitialized())
	{
		messageSocket->CreateClient();
		IPC_RETURN();
	}
	else
	{
		messageSocket->DestroyClient();
		messageSocket->CreateClient();
		IPC_RETURN();
	}
}

IPC_API_EX(subscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->SubscribeToEvent(params["eventName"].get<std::string>());
		IPC_RETURN();
	}
	return RETURN_ERROR("Unable to find `eventName` in `subscribe_event` IPC API.");
}

IPC_API_EX(unsubscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->UnsubscribeToEvent(params["eventName"].get<std::string>());
		IPC_RETURN();
	}
	return RETURN_ERROR("Unable to find `eventName` in `unsubscribe_event` IPC API.");
}
