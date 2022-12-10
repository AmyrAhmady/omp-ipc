#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Player_SendMessage, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["ptr"], player);
	player->sendClientMessage(Colour::FromRGBA(params["color"]), params["text"]);
	return NO_DATA_SUCCESS_RETURN;
}
