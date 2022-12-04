#include "../message/Handler.hpp"
#include "./Manager.hpp"

IPC_API(sendClientMessage, const nlohmann::json& params)
{
	IPlayer* player = GetPlayer(params["playerId"]);
	if (player)
	{
		player->sendClientMessage(Colour::White(), params["text"]);
	}
	return UNDEFINED_FAILED_RETURN;
}
