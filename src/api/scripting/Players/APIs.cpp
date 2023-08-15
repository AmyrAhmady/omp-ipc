#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Player_SendMessage, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->sendClientMessage(Colour::FromRGBA(params["color"]), params["text"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetCameraPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setCameraPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetDrunkLevel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setDrunkLevel(params["level"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetInterior, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setInterior(params["interiorid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetWantedLevel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setWantedLevel(params["level"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetWeather, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setWeather(params["weatherid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetSkin, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setSkin(params["skinid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetShopName, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setShopName(params["name"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GiveMoney, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->giveMoney(params["amount"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetCameraLookAt, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setCameraLookAt({ params["x"], params["y"], params["z"] }, params["cutType"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetCameraBehind, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setCameraBehind();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_CreateExplosion, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->createExplosion({ params["x"], params["y"], params["z"] }, params["type"], params["radius"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_PlayAudioStream, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->playAudio(params["url"], params["usePos"], { params["x"], params["y"], params["z"] }, params["distance"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_StopAudioStream, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->stopAudio();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ToggleWidescreen, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useWidescreen(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetHealth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setHealth(params["health"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetArmour, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setArmour(params["armour"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetTeam, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setTeam(params["teamid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetScore, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setScore(params["score"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_RemoveWeapon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->removeWeapon(params["weaponid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ResetMoney, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->resetMoney();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ToggleClock, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useClock(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ForceClassSelection, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->forceClassSelection();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetVelocity, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setVelocity({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_PlaySound, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->playSound(params["sound"], { params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setVirtualWorld(params["vw"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_PutInVehicle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["vehicle"], vehicle);
	vehicle->putPlayer(*player, params["seatID"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_RemoveBuilding, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->removeDefaultObjects(params["model"], { params["x"], params["y"], params["z"] }, params["radius"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_RemoveMapIcon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->unsetMapIcon(params["iconID"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ResetWeapons, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->resetWeapons();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetArmedWeapon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setArmedWeapon(params["weapon"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetPosFindZ, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setPositionFindZ({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ShowNameTagForPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["other"], other);
	player->toggleOtherNameTag(*other, params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ToggleControllable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setControllable(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ToggleSpectating, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setSpectating(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_EnableCameraTarget, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useCameraTargeting(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_EnableStuntBonus, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useStuntBonuses(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_AttachCameraToObject, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	player->attachCameraToObject(*object);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_DisableRemoteVehicleCollisions, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setRemoteVehicleCollisions(!params["disable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SendCheck, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->sendClientCheck(params["actionType"], params["address"], params["offset"], params["count"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_Spawn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->spawn();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_Kick, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->kick();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_HideGameText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->hideGameText(params["style"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_Ban, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->ban();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetGravity, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setGravity(params["gravity"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_ToggleGhostMode, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->toggleGhostMode(params["toggle"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_AllowWeapons, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->allowWeapons(params["allow"]);
	return NO_DATA_SUCCESS_RETURN;
}
