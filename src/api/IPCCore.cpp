#include "../message/Handler.hpp"
#include "../message/Socket.hpp"

IPC_API_EX(create_omp_ipc_client, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (!messageSocket->IsClientInitialized())
	{
		messageSocket->CreateClient();
		return NO_DATA_SUCCESS_RETURN;
	}
	else
	{
		messageSocket->DestroyClient();
		messageSocket->CreateClient();
		return NO_DATA_SUCCESS_RETURN;
	}
}

IPC_API_EX(subscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->SubscribeToEvent(params["eventName"].get<std::string>());
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}

IPC_API_EX(unsubscribe_event, const nlohmann::json& params, MessageSocket* messageSocket)
{
	if (params.count("eventName"))
	{
		messageSocket->UnsubscribeToEvent(params["eventName"].get<std::string>());
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}
