#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Player_SendMessage, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->sendClientMessage(Colour::FromRGBA(params["color"]), params["text"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Core_SendMessageToAll, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_SetCameraPosition, const nlohmann::json& params)
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

IPC_API(Player_GetWeather, const nlohmann::json& params)
{
    // TODO
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

IPC_API(Core_CreateExplosion, const nlohmann::json& params)
{
    // TODO
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

IPC_API(Player_SendDeathMessage, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_ToggleWidescreen, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useWidescreen(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_IsWidescreenToggled, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->hasWidescreen());
}

IPC_API(Player_SetHealth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setHealth(params["health"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetHealth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getHealth());
}

IPC_API(Player_SetArmour, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setArmour(params["armour"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetArmour, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getArmour());
}

IPC_API(Player_SetTeam, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setTeam(params["teamid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetTeam, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_SetScore, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setScore(params["score"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetScore, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getScore());
}

IPC_API(Player_GetSkin, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getSkin());
}

IPC_API(Player_SetColour, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    player->setColour(Colour::FromRGBA(params["colour"]));
    return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetColour, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    return RETURN_VALUE(player->getColour().RGBA());
}

IPC_API(Player_GetDefaultColour, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetDrunkLevel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getDrunkLevel());
}

IPC_API(Player_GiveWeapon, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_RemoveWeapon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->removeWeapon(params["weaponid"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetMoney, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getMoney());
}

IPC_API(Player_ResetMoney, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->resetMoney();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetName, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetName, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetState, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getState());
}

IPC_API(Player_GetPing, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetWeapon, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_SetTime, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setTime(std::chrono::hours(params["hour"]), std::chrono::minutes(params["minute"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetTime, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_ToggleClock, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->useClock(params["enable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_HasClockEnabled, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->hasClock());
}

IPC_API(Player_ForceClassSelection, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->forceClassSelection();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetWantedLevel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getWantedLevel());
}

IPC_API(Player_SetFightingStyle, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setFightingStyle(PlayerFightingStyle(params["style"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetFightingStyle, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_SetVelocity, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setVelocity({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetVelocity, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetCameraPosition, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetDistanceFromPoint, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetInterior, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getInterior());
}

IPC_API(Player_SetPosition, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetPosition, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getVirtualWorld());
}

IPC_API(Player_IsNPC, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_IsStreamedIn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["other"], other);
	return RETURN_VALUE(player->isStreamedInForPlayer(*other));
}

IPC_API(Player_PlaySound, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->playSound(params["sound"], { params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SpectatePlayer, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["target"], target);
    player->spectatePlayer(*target, PlayerSpectateMode(params["mode"]));
    return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SpectateVehicle, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["target"], target);
    player->spectateVehicle(*target, PlayerSpectateMode(params["mode"]));
    return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setVirtualWorld(params["vw"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetWorldBounds, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetWorldBounds, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_ClearAnimations, const nlohmann::json& params)
{
    // TODO: This must be fixed on client side
	// At the moment ClearAnimations flushes all tasks applied to player
	// Including driving, siting in vehicle, shooting, jumping, or any sort of a task
	// And it doesn't just clear applied animations, in order to keep it compatible with
	// Current samp scripts without requiring a change, we call IPlayer::clearTasks temporarily.
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
    player->clearTasks(PlayerAnimationSyncType(params["syncType"]));
    return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetLastShotVectors, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerCameraTargetPlayer, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerCameraTargetActor, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerCameraTargetObject, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerCameraTargetVehicle, const nlohmann::json& params)
{
    // TODO
}

IPC_API(IsPlayerConnected, const nlohmann::json& params)
{
    // TODO
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

IPC_API(Player_GetBuildingsRemoved, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getDefaultObjectsRemoved());
}

IPC_API(RemovePlayerFromVehicle, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_RemoveMapIcon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->unsetMapIcon(params["iconID"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(SetPlayerMapIcon, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_ResetWeapons, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->resetWeapons();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(SetPlayerAmmo, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_SetArmedWeapon, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setArmedWeapon(params["weapon"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetChatBubble, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setChatBubble(params["text"], Colour::FromRGBA(params["colour"]), params["drawdistance"], std::chrono::milliseconds(params["expiretime"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetPositionFindZ, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setPositionFindZ({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetSkillLevel, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setSkillLevel(PlayerWeaponSkill(params["weapon"]), params["level"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_SetSpecialAction, const nlohmann::json& params)
{
    GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	player->setAction(PlayerSpecialAction(params["action"]));
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

IPC_API(ApplyAnimation, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetAnimationName, const nlohmann::json& params)
{
    // TODO
}

IPC_API(EditAttachedObject, const nlohmann::json& params)
{
    // TODO
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

IPC_API(EnableStuntBonusForAll, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetAmmo, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getArmedWeaponAmmo());
}

IPC_API(Player_GetAnimationIndex, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getAnimationData().ID);
}

IPC_API(GetPlayerFacingAngle, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerIp, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetSpecialAction, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getAction());
}

IPC_API(GetPlayerVehicleID, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerVehicleSeat, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerWeaponData, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetWeaponState, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getAimData().weaponState);
}

IPC_API(InterpolateCameraPos, const nlohmann::json& params)
{
    // TODO
}

IPC_API(InterpolateCameraLookAt, const nlohmann::json& params)
{
    // TODO
}

IPC_API(IsPlayerAttachedObjectSlotUsed, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_AttachCameraToObject, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	player->attachCameraToObject(*object);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(AttachCameraToPlayerObject, const nlohmann::json& params)
{
    // TODO
}

IPC_API(Player_GetCameraAspectRatio, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(player->getAimData().aspectRatio);
}

IPC_API(GetPlayerCameraFrontVector, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerCameraMode, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerKeys, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerSurfingVehicleID, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerSurfingObjectID, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerTargetPlayer, const nlohmann::json& params)
{
    // TODO
}

IPC_API(GetPlayerTargetActor, const nlohmann::json& params)
{
    // TODO
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
