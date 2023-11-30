#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Player_SendMessage, uintptr_t player, uint32_t color, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->sendClientMessage(Colour::FromRGBA(color), text);
	IPC_RETURN();
}

IPC_API(All_SendMessage, uint32_t colour, ConstStringRef text)
{
	OmpManager::Get()->players->sendClientMessageToAll(Colour::FromRGBA(colour), text);
	IPC_RETURN();
}

IPC_API(Player_SetCameraPos, uintptr_t player, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setCameraPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Player_SetDrunkLevel, uintptr_t player, int level)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setDrunkLevel(level);
	IPC_RETURN();
}

IPC_API(Player_SetInterior, uintptr_t player, int interior)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setInterior(interior);
	IPC_RETURN();
}

IPC_API(SetPlayerWantedLevel, uintptr_t player, int level)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setWantedLevel(level);
	IPC_RETURN();
}

IPC_API(SetPlayerWeather, uintptr_t player, int weather)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setWeather(weather);
	IPC_RETURN();
}

IPC_API(Player_GetWeather, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int weather = player_->getWeather();
	IPC_RETURN(int weather);
}

IPC_API(Player_SetSkin, uintptr_t player, int skin)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setSkin(skin);
	IPC_RETURN();
}

IPC_API(Player_SetShopName, uintptr_t player, ConstStringRef name)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setShopName(name);
	IPC_RETURN();
}

IPC_API(Player_GiveMoney, uintptr_t player, int amount)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->giveMoney(amount);
	IPC_RETURN();
}

IPC_API(Player_SetCameraLookAt, uintptr_t player, float x, float y, float z, int cutType)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setCameraLookAt({ x, y, z }, cutType);
	IPC_RETURN();
}

IPC_API(Player_SetCameraBehind, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setCameraBehind();
	IPC_RETURN();
}

IPC_API(Player_CreateExplosion, uintptr_t player, float x, float y, float z, int type, float radius)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->createExplosion({ x,y,z }, type, radius);
	IPC_RETURN();
}

IPC_API(All_CreateExplosion, float x, float y, float z, int type, float radius)
{
	OmpManager::Get()->players->createExplosionForAll({ x,y,z }, type, radius);
	IPC_RETURN();
}

IPC_API(Player_PlayAudioStream, uintptr_t player, ConstStringRef url, float x, float y, float z, float distance, bool usePos)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->playAudio(url, usePos, { x, y, z }, distance);
	IPC_RETURN();
}

IPC_API(Player_StopAudioStream, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->stopAudio();
	IPC_RETURN();
}

IPC_API(All_SendDeathMessage, uintptr_t killer, uintptr_t killee, int weapon)
{
	if (killee)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, killer, killer_);
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, killee, killee_);
		OmpManager::Get()->players->sendDeathMessageToAll(killer_, *killee_, weapon);
	}
	else
	{
		OmpManager::Get()->players->sendEmptyDeathMessageToAll();
	}
	IPC_RETURN();
}

IPC_API(Player_ToggleWidescreen, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useWidescreen(enable);
	IPC_RETURN();
}

IPC_API(Player_IsWidescreenToggled, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto enabled = player_->hasWidescreen();
	IPC_RETURN(bool enabled);
}

IPC_API(Player_SetHealth, uintptr_t player, float health)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setHealth(health);
	IPC_RETURN();
}

IPC_API(Player_GetHealth, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto health = player_->getHealth();
	IPC_RETURN(float health);
}

IPC_API(Player_SetArmor, uintptr_t player, float armor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setArmour(armor);
	IPC_RETURN();
}

IPC_API(Player_GetArmor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	float armor = player_->getArmour();
	IPC_RETURN(float armor);
}

IPC_API(SetPlayerTeam, uintptr_t player, int team)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setTeam(team);
	IPC_RETURN();
}

IPC_API(Player_GetTeam, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto team = player_->getTeam();
	IPC_RETURN(int team);
}

IPC_API(Player_SetScore, uintptr_t player, int score)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setScore(score);
	IPC_RETURN();
}

IPC_API(Player_GetScore, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto score = player_->getScore();
	IPC_RETURN(int score);
}

IPC_API(Player_GetSkin, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto skin = player_->getSkin();
	IPC_RETURN(int skin);
}

IPC_API(Player_SetColor, uintptr_t player, uint32_t color)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setColour(Colour::FromRGBA(color));
	IPC_RETURN();
}

IPC_API(Player_GetColor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto color = player_->getColour().RGBA();
	IPC_RETURN(uint32_t color);
}

IPC_API(Player_GetDefaultColor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	// The player doesn't need to be connected for this to work.
	auto color = OmpManager::Get()->players->getDefaultColour(player_->getID()).RGBA();
	IPC_RETURN(uint32_t color);
}

IPC_API(Player_GetDrunkLevel, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto level = player_->getDrunkLevel();
	IPC_RETURN(int level);
}

IPC_API(Player_GiveWeapon, uintptr_t player, int weapon, int ammo)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	WeaponSlotData data;
	data.id = weapon;
	data.ammo = ammo;
	player_->giveWeapon(data);
	IPC_RETURN();
}

IPC_API(Player_RemoveWeapon, uintptr_t player, int weapon)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->removeWeapon(weapon);
	IPC_RETURN();
}

IPC_API(Player_GetMoney, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto money = player_->getMoney();
	IPC_RETURN(int money);
}

IPC_API(Player_ResetMoney, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->resetMoney();
	IPC_RETURN();
}

IPC_API(Player_SetName, uintptr_t player, ConstStringRef name)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int status = int(player_->setName(name));
	IPC_RETURN(int status);
}

IPC_API(Player_GetName, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	ConstStringRef name = player_->getName().data();
	int len = name.length();
	IPC_RETURN(ConstStringRef name, int len);
}

IPC_API(Player_GetState, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int state = player_->getState();
	IPC_RETURN(int state);
}

IPC_API(Player_GetPing, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int ping = player_->getPing();
	IPC_RETURN(int ping);
}

IPC_API(Player_GetWeapon, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int weapon = player_->getArmedWeapon();
	IPC_RETURN(int weapon);
}

IPC_API(Player_SetTime, uintptr_t player, int hour, int minute)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setTime(std::chrono::hours(hour), std::chrono::minutes(minute));
	IPC_RETURN();
}

IPC_API(Player_GetTime, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	std::pair<std::chrono::hours, std::chrono::minutes> data = player_->getTime();
	int hour = data.first.count();
	int minute = data.second.count();
	IPC_RETURN(int hour, int minute);
}

IPC_API(Player_ToggleClock, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useClock(enable);
	IPC_RETURN();
}

IPC_API(Player_HasClock, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto enable = player_->hasClock();
	IPC_RETURN(int enable);
}

IPC_API(Player_ForceClassSelection, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->forceClassSelection();
	IPC_RETURN();
}

IPC_API(Player_GetWantedLevel, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto wanted = player_->getWantedLevel();
	IPC_RETURN(int wanted);
}

IPC_API(Player_SetFightingStyle, uintptr_t player, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setFightingStyle(PlayerFightingStyle(style));
	IPC_RETURN();
}

IPC_API(Player_GetFightingStyle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int style = int(player_->getFightingStyle());
	IPC_RETURN(int style);
}

IPC_API(Player_SetVelocity, uintptr_t player, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setVelocity({ x, y, z });
	IPC_RETURN();
}

IPC_API(Player_GetVelocity, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto velocity = player_->getVelocity();
	float x = velocity.x;
	float y = velocity.y;
	float z = velocity.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Player_GetCameraPos, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto pos = player_->getAimData().camPos;
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	IPC_RETURN(float x, float y, float z);
}
/*
IPC_API(GetPlayerDistanceFromPoint, float(IPlayer& player, Vector3 pos))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Vector3 playerCoords = player_->getPosition();
	return glm::distance(playerCoords, pos);
}

IPC_API(GetPlayerInterior, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getInterior();
}

IPC_API(SetPlayerPos, bool(IPlayer& player, Vector3 vec))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setPosition(vec);
	return true;
}

IPC_API(GetPlayerPos, bool(IPlayer& player, Vector3& pos))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	pos = player_->getPosition();
	return true;
}

IPC_API(GetPlayerVirtualWorld, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getVirtualWorld();
}

IPC_API(IsPlayerNPC, bool(IPlayer* player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player != nullptr && player->isBot();
}

IPC_API(IsPlayerStreamedIn, bool(IPlayer& player, IPlayer& other))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->isStreamedInForPlayer(other);
}

IPC_API(PlayerPlaySound, bool(IPlayer& player, uint32_t sound, Vector3 pos))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->playSound(sound, pos);
	return true;
}

IPC_API(PlayerSpectatePlayer, bool(IPlayer& player, IPlayer& target, int mode))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->spectatePlayer(target, PlayerSpectateMode(mode));
	return true;
}

IPC_API(PlayerSpectateVehicle, bool(IPlayer& player, IVehicle& target, int mode))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->spectateVehicle(target, PlayerSpectateMode(mode));
	return true;
}

IPC_API(SetPlayerVirtualWorld, bool(IPlayer& player, int vw))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setVirtualWorld(vw);
	return true;
}

IPC_API(SetPlayerWorldBounds, bool(IPlayer& player, float xMax, float xMin, float yMax, float yMin))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Vector4 coords = { xMax, xMin, yMax, yMin };
	player_->setWorldBounds(coords);
	return true;
}

IPC_API(ClearPlayerWorldBounds, bool(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setWorldBounds(Vector4(MAX_WORLD_BOUNDS, MIN_WORLD_BOUNDS, MAX_WORLD_BOUNDS, MIN_WORLD_BOUNDS));
	return true;
}

IPC_API(GetPlayerWorldBounds, bool(IPlayer& player, Vector4& bounds))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bounds = player_->getWorldBounds();
	return true;
}

IPC_API(ClearAnimations, bool(IPlayer& player, int syncType))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	// TODO: This must be fixed on client side
	// At the moment ClearAnimations flushes all tasks applied to player
	// Including driving, siting in vehicle, shooting, jumping, or any sort of a task
	// And it doesn't just clear applied animations, in order to keep it compatible with
	// Current samp scripts without requiring a change, we call IPlayer::clearTasks temporarily.
	player_->clearTasks(PlayerAnimationSyncType(syncType));
	return true;
}

IPC_API(GetPlayerLastShotVectors, bool(IPlayer& player, Vector3& origin, Vector3& hitPos))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerBulletData data = player_->getBulletData();
	origin = data.origin;
	hitPos = data.hitPos;
	return true;
}

IPC_API_FAILRET(GetPlayerCameraTargetPlayer, INVALID_PLAYER_ID, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayer* target = player_->getCameraTargetPlayer();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerCameraTargetActor, INVALID_ACTOR_ID, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IActor* target = player_->getCameraTargetActor();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerCameraTargetObject, INVALID_OBJECT_ID, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IObject* target = player_->getCameraTargetObject();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerCameraTargetVehicle, INVALID_VEHICLE_ID, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IVehicle* target = player_->getCameraTargetVehicle();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API(IsPlayerConnected, bool(IPlayer* player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player != nullptr;
}

IPC_API(PutPlayerInVehicle, bool(IPlayer& player, IVehicle& vehicle, int seatID))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	vehicle.putPlayer(player, seatID);
	return true;
}

IPC_API(RemoveBuildingForPlayer, bool(IPlayer& player, uint32_t model, Vector3 pos, float radius))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->removeDefaultObjects(model, pos, radius);
	return true;
}

IPC_API(GetPlayerBuildingsRemoved, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getDefaultObjectsRemoved();
}

IPC_API(RemovePlayerFromVehicle, bool(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	cell* args = GetParams();
	player_->removeFromVehicle(args[0] == 2 * sizeof(cell) && args[2]);
	return true;
}

IPC_API(RemovePlayerMapIcon, bool(IPlayer& player, int iconID))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->unsetMapIcon(iconID);
	return true;
}

IPC_API(SetPlayerMapIcon, bool(IPlayer& player, int iconID, Vector3 pos, int type, uint32_t colour, int style))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setMapIcon(iconID, pos, type, Colour::FromRGBA(colour), MapIconStyle(style));
	return true;
}

IPC_API(ResetPlayerWeapons, bool(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->resetWeapons();
	return true;
}

IPC_API(SetPlayerAmmo, bool(IPlayer& player, uint8_t id, uint32_t ammo))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	WeaponSlotData data;
	data.id = id;
	data.ammo = ammo;
	player_->setWeaponAmmo(data);
	return true;
}

IPC_API(SetPlayerArmedWeapon, bool(IPlayer& player, uint8_t weapon))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setArmedWeapon(weapon);
	return true;
}

IPC_API(SetPlayerChatBubble, bool(IPlayer& player, cell const* format, uint32_t colour, float drawdistance, int expiretime))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	AmxStringFormatter text(format, GetAMX(), GetParams(), 5);
	player_->setChatBubble(text, Colour::FromRGBA(colour), drawdistance, std::chrono::milliseconds(expiretime));
	return true;
}

IPC_API(SetPlayerPosFindZ, bool(IPlayer& player, Vector3 pos))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setPositionFindZ(pos);
	return true;
}

IPC_API(SetPlayerSkillLevel, bool(IPlayer& player, uint8_t weapon, int level))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setSkillLevel(PlayerWeaponSkill(weapon), level);
	return true;
}

IPC_API(SetPlayerSpecialAction, bool(IPlayer& player, uint32_t action))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setAction(PlayerSpecialAction(action));
	return true;
}

IPC_API(ShowPlayerNameTagForPlayer, bool(IPlayer& player, IPlayer& other, bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->toggleOtherNameTag(other, enable);
	return true;
}

IPC_API(TogglePlayerControllable, bool(IPlayer& player, bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setControllable(enable);
	return true;
}

IPC_API(TogglePlayerSpectating, bool(IPlayer& player, bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setSpectating(enable);
	return true;
}

IPC_API(ApplyAnimation, bool(IPlayer& player, const std::string& animlib, const std::string& animname, float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, int sync))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	const AnimationData animationData(delta, loop, lockX, lockY, freeze, time, animlib, animname);
	player_->applyAnimation(animationData, PlayerAnimationSyncType(sync));
	return true;
}

IPC_API(GetAnimationName, bool(int index, OutputOnlyString& lib, OutputOnlyString& name))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Pair<StringView, StringView> anim = splitAnimationNames(index);
	lib = anim.first;
	name = anim.second;
	return true;
}

IPC_API(EditAttachedObject, bool(IPlayerObjectData& data, int index))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	data.editAttachedObject(index);
	return true;
}

IPC_API(EnablePlayerCameraTarget, bool(IPlayer& player, bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useCameraTargeting(enable);
	return true;
}

IPC_API(EnableStuntBonusForPlayer, bool(IPlayer& player, bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useStuntBonuses(enable);
	return true;
}

IPC_API(EnableStuntBonusForAll, bool(bool enable))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PawnManager::Get()->core->useStuntBonuses(enable);
	return true;
}

IPC_API(GetPlayerAmmo, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getArmedWeaponAmmo();
}

IPC_API(GetPlayerAnimationIndex, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getAnimationData().ID;
}

IPC_API(GetPlayerFacingAngle, bool(IPlayer& player, float& angle))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GTAQuat quat = player_->getRotation();
	angle = quat.ToEuler().z;
	return true;
}

IPC_API_FAILRET(GetPlayerIp, -1, int(IPlayer& player, OutputOnlyString& ip))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PeerNetworkData data = player_->getNetworkData();
	if (!data.networkID.address.ipv6)
	{
		PeerAddress::AddressString addressString;
		if (PeerAddress::ToString(data.networkID.address, addressString))
		{
			// Scope-allocated string, copy it
			ip = String(StringView(addressString));
			return std::get<String>(ip).length();
		}
	}
	return FailRet;
}

IPC_API(GetPlayerSpecialAction, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getAction();
}

IPC_API_FAILRET(GetPlayerVehicleID, INVALID_VEHICLE_ID, int(IPlayerVehicleData& data))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IVehicle* vehicle = data.getVehicle();
	if (vehicle)
	{
		return vehicle->getID();
	}
	return 0;
}

IPC_API_FAILRET(GetPlayerVehicleSeat, SEAT_NONE, int(IPlayerVehicleData& data))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return data.getSeat();
}

IPC_API(GetPlayerWeaponData, bool(IPlayer& player, int slot, int& weaponid, int& ammo))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	if (slot < 0 || slot >= MAX_WEAPON_SLOTS)
	{
		return false;
	}
	const WeaponSlotData& weapon = player_->getWeaponSlot(slot);
	weaponid = weapon.id;
	ammo = weapon.ammo;
	return true;
}

IPC_API(GetPlayerWeaponState, int(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getAimData().weaponState;
}

IPC_API(InterpolateCameraPos, bool(IPlayer& player, Vector3 from, Vector3 to, int time, int cut))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->interpolateCameraPosition(from, to, time, PlayerCameraCutType(cut));
	return true;
}

IPC_API(InterpolateCameraLookAt, bool(IPlayer& player, Vector3 from, Vector3 to, int time, int cut))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->interpolateCameraLookAt(from, to, time, PlayerCameraCutType(cut));
	return true;
}

IPC_API(IsPlayerAttachedObjectSlotUsed, bool(IPlayerObjectData& data, int index))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return data.hasAttachedObject(index);
}

IPC_API(AttachCameraToObject, bool(IPlayer& player, IObject& object))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->attachCameraToObject(object);
	return true;
}

IPC_API(AttachCameraToPlayerObject, bool(IPlayer& player, IPlayerObject& object))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->attachCameraToObject(object);
	return true;
}

IPC_API(GetPlayerCameraAspectRatio, float(IPlayer& player))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getAimData().aspectRatio;
}

IPC_API(GetPlayerCameraFrontVector, bool(IPlayer& player, Vector3& vector))
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	vector = player_->getAimData().camFrontVector;
	return true;
}

IPC_API_FAILRET(GetPlayerCameraMode, -1, int(IPlayer& player))
{
	return player_->getAimData().camMode;
}

IPC_API(GetPlayerKeys, bool(IPlayer& player, int& keys, int& updown, int& leftright))
{
	const PlayerKeyData& keyData = player_->getKeyData();
	keys = keyData.keys;
	updown = keyData.upDown;
	leftright = keyData.leftRight;
	return true;
}

IPC_API_FAILRET(GetPlayerSurfingVehicleID, INVALID_VEHICLE_ID, int(IPlayer& player))
{
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Vehicle)
	{
		IVehiclesComponent* vehicles = PawnManager::Get()->vehicles;
		if (vehicles && vehicles->get(data.ID))
		{
			return data.ID;
		}
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerSurfingObjectID, INVALID_OBJECT_ID, int(IPlayer& player))
{
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Object)
	{
		IObjectsComponent* objects = PawnManager::Get()->objects;
		if (objects && objects->get(data.ID))
		{
			return data.ID;
		}
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerTargetPlayer, INVALID_PLAYER_ID, int(IPlayer& player))
{
	IPlayer* target = player_->getTargetPlayer();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API_FAILRET(GetPlayerTargetActor, INVALID_PLAYER_ID, int(IPlayer& player))
{
	IActor* target = player_->getTargetActor();
	if (target)
	{
		return target->getID();
	}
	return FailRet;
}

IPC_API(IsPlayerInVehicle, bool(IPlayerVehicleData& data, IVehicle& targetVehicle))
{
	IVehicle* vehicle = data.getVehicle();
	return vehicle == &targetVehicle;
}

IPC_API(IsPlayerInAnyVehicle, bool(IPlayerVehicleData& data))
{
	IVehicle* vehicle = data.getVehicle();
	return vehicle != nullptr;
}

IPC_API(IsPlayerInRangeOfPoint, bool(IPlayer& player, float range, Vector3 position))
{
	return range >= glm::distance(player_->getPosition(), position);
}

IPC_API(PlayCrimeReportForPlayer, bool(IPlayer& player, IPlayer& suspect, int crime))
{
	return player_->playerCrimeReport(suspect, crime);
}

IPC_API(RemovePlayerAttachedObject, bool(IPlayerObjectData& data, int index))
{
	data.removeAttachedObject(index);
	return true;
}

IPC_API(SetPlayerAttachedObject, bool(IPlayerObjectData& data, int index, int modelid, int bone, Vector3 offset, Vector3 rotation, Vector3 scale, uint32_t materialcolor1, uint32_t materialcolor2))
{
	ObjectAttachmentSlotData attachment;
	attachment.model = modelid;
	attachment.bone = bone;
	attachment.offset = offset;
	attachment.rotation = rotation;
	attachment.scale = scale;
	attachment.colour1 = Colour::FromARGB(materialcolor1);
	attachment.colour2 = Colour::FromARGB(materialcolor2);
	data.setAttachedObject(index, attachment);
	return true;
}

IPC_API(GetPlayerAttachedObject, bool(IPlayerObjectData& data, int index, int& modelid, int& bone, Vector3& offset, Vector3& rotation, Vector3& scale, uint32_t& materialcolor1, uint32_t& materialcolor2))
{
	ObjectAttachmentSlotData attachment = data.getAttachedObject(index);
	modelid = attachment.model;
	bone = attachment.bone;
	offset = attachment.offset;
	rotation = attachment.rotation;
	scale = attachment.scale;
	materialcolor1 = attachment.colour1.ARGB();
	materialcolor2 = attachment.colour2.ARGB();
	return true;
}

IPC_API(SetPlayerFacingAngle, bool(IPlayer& player, float angle))
{
	Vector3 rotation = player_->getRotation().ToEuler();
	rotation.z = angle;
	player_->setRotation(rotation);
	return true;
}

IPC_API(SetPlayerMarkerForPlayer, bool(IPlayer& player, IPlayer& other, uint32_t colour))
{
	player_->setOtherColour(other, Colour::FromRGBA(colour));
	return true;
}

IPC_API(GetPlayerMarkerForPlayer, int(IPlayer& player, IPlayer& other))
{
	Colour colour;
	bool hasPlayerSpecificColour = player_->getOtherColour(other, colour);
	if (!hasPlayerSpecificColour)
	{
		colour = other.getColour();
	}
	return colour.RGBA();
}

IPC_API(AllowPlayerTeleport, bool(IPlayer* player, bool allow))
{
	player->allowTeleport(allow);
	return true;
}

IPC_API(IsPlayerTeleportAllowed, bool(IPlayer* player))
{
	return player->isTeleportAllowed();
}

IPC_API(DisableRemoteVehicleCollisions, bool(IPlayer& player, bool disable))
{
	player_->setRemoteVehicleCollisions(!disable);
	return true;
}

IPC_API(GetPlayerCameraZoom, float(IPlayer& player))
{
	return player_->getAimData().camZoom;
}

IPC_API(SelectTextDraw, bool(IPlayerTextDrawData& data, uint32_t hoverColour))
{
	data.beginSelection(Colour::FromRGBA(hoverColour));
	return true;
}

IPC_API(CancelSelectTextDraw, bool(IPlayerTextDrawData& data))
{
	data.endSelection();
	return true;
}

IPC_API(SendClientCheck, bool(IPlayer& player, int actionType, int address, int offset, int count))
{
	player_->sendClientCheck(actionType, address, offset, count);
	return true;
}

IPC_API(SpawnPlayer, bool(IPlayer& player))
{
	player_->spawn();
	return true;
}

IPC_API(gpci, int(IPlayer& player, OutputOnlyString& output))
{
	output = player_->getSerial();
	return std::get<StringView>(output).length();
}

IPC_API(IsPlayerAdmin, bool(IPlayerConsoleData& data))
{
	return data.hasConsoleAccess();
}

IPC_API(Kick, bool(IPlayer& player))
{
	player_->kick();
	return true;
}

IPC_API(GameTextForPlayer, bool(IPlayer& player, cell const* format, int time, int style))
{
	AmxStringFormatter string(format, GetAMX(), GetParams(), 4);
	if (string.empty())
	{
		return false;
	}
	player_->sendGameText(string, Milliseconds(time), style);
	return true;
}

IPC_API(HideGameTextForPlayer, bool(IPlayer& player, int style))
{
	player_->hideGameText(style);
	return true;
}

IPC_API(HasGameText, bool(IPlayer& player, int style))
{
	return player_->hasGameText(style);
}

IPC_API(GetGameText, bool(IPlayer& player, int style, OutputOnlyString& message, int time, int remaining))
{
	Milliseconds mt;
	Milliseconds mr;
	StringView ms;
	if (player_->getGameText(style, ms, mt, mr))
	{
		message = ms;
		time = (int)mt.count();
		remaining = (int)mr.count();
		return true;
	}
	return false;
}

IPC_API(GameTextForPlayerf, bool(IPlayer& player, int time, int style, cell const* format))
{
	AmxStringFormatter string(format, GetAMX(), GetParams(), 4);
	if (string.empty())
	{
		return false;
	}
	player_->sendGameText(string, Milliseconds(time), style);
	return true;
}

IPC_API(Ban, bool(IPlayer& player))
{
	player_->ban();
	return true;
}

IPC_API(BanEx, bool(IPlayer& player, cell const* format))
{
	AmxStringFormatter reason(format, GetAMX(), GetParams(), 2);
	player_->ban(reason);
	return true;
}

IPC_API(SendDeathMessageToPlayer, bool(IPlayer& player, IPlayer* killer, IPlayer* killee, int weapon))
{
	if (killee)
	{
		player_->sendDeathMessage(*killee, killer, weapon);
	}
	else
	{
		player_->sendEmptyDeathMessage();
	}
	return true;
}

IPC_API(SendPlayerMessageToPlayer, bool(IPlayer& player, IPlayer& sender, cell const* format))
{
	AmxStringFormatter message(format, GetAMX(), GetParams(), 3);
	player_->sendChatMessage(sender, message);
	return true;
}

IPC_API(SendPlayerMessageToPlayerf, bool(IPlayer& player, IPlayer& sender, cell const* format))
{
	AmxStringFormatter message(format, GetAMX(), GetParams(), 3);
	player_->sendChatMessage(sender, message);
	return true;
}

IPC_API(GetPlayerVersion, int(IPlayer& player, OutputOnlyString& version))
{
	version = player_->getClientVersionName();
	return std::get<StringView>(version).length();
}

IPC_API(GetPlayerSkillLevel, int(IPlayer& player, int skill))
{
	auto skills = player_->getSkillLevels();
	if (skill >= 11 || skill < 0)
	{
		return 0;
	}
	return skills[skill];
}

IPC_API(GetPlayerZAim, float(IPlayer& player))
{
	return player_->getAimData().aimZ;
}

IPC_API(GetPlayerSurfingOffsets, bool(IPlayer& player, Vector3& offset))
{
	const PlayerSurfingData& data = player_->getSurfingData();

	if (data.type != PlayerSurfingData::Type::None)
	{
		offset = data.offset;
	}
	return true;
}

IPC_API(GetPlayerRotationQuat, bool(IPlayer& player, Vector4& quat))
{
	glm::quat rotQuat = player_->getRotation().q;

	// In samp or YSF, GetPlayerRotationQuat declaration is like this:
	// GetPlayerRotationQuat(playerid, &Float:w, &Float:x = 0.0, &Float:y = 0.0, &Float:z = 0.0);
	// Meaning first output arg is W and not X; Vector4's first member is X and it is used in many other places,
	// We can't just simply change ParamCast for Vector4 just because one function doesn't follow it.
	quat.x = rotQuat.w;
	quat.y = rotQuat.x;
	quat.z = rotQuat.y;
	quat.w = rotQuat.z;
	return true;
}

IPC_API(GetPlayerSpectateID, int(IPlayer& player))
{
	return player_->getSpectateData().spectateID;
}

IPC_API(GetPlayerSpectateType, int(IPlayer& player))
{
	return int(player_->getSpectateData().type);
}

IPC_API(GetPlayerRawIp, int(IPlayer& player))
{
	return player_->getNetworkData().networkID.address.v4;
}

IPC_API(SetPlayerGravity, bool(IPlayer& player, float gravity))
{
	player_->setGravity(gravity);
	return true;
}

IPC_API(GetPlayerGravity, float(IPlayer& player))
{
	return player_->getGravity();
}

IPC_API(SetPlayerAdmin, bool(IPlayerConsoleData& data, bool set))
{
	data.setConsoleAccessibility(set);
	return true;
}

IPC_API(IsPlayerSpawned, bool(IPlayer& player))
{
	PlayerState state = player_->getState();
	switch (state)
	{
	case PlayerState_OnFoot:
	case PlayerState_Driver:
	case PlayerState_Passenger:
	case PlayerState_Spawned:
	{
		return true;
	}
	default:
		return false;
	}
}

IPC_API(IsPlayerControllable, bool(IPlayer& player))
{
	return player_->getControllable();
}

IPC_API(IsPlayerCameraTargetEnabled, bool(IPlayer& player))
{
	return player_->hasCameraTargeting();
}

IPC_API(TogglePlayerGhostMode, bool(IPlayer& player, bool toggle))
{
	player_->toggleGhostMode(toggle);
	return true;
}

IPC_API(GetPlayerGhostMode, bool(IPlayer& player))
{
	return player_->isGhostModeEnabled();
}

IPC_API(AllowPlayerWeapons, bool(IPlayer& player, bool allow))
{
	player_->allowWeapons(allow);
	return true;
}

IPC_API(ArePlayerWeaponsAllowed, bool(IPlayer& player))
{
	return player_->areWeaponsAllowed();
}

IPC_API(IsPlayerUsingOfficialClient, int(IPlayer& player))
{
	return player_->isUsingOfficialClient();
}

IPC_API(GetPlayerAnimFlags, int(IPlayer& player))
{
	PlayerAnimationData data = player_->getAnimationData();
	return data.flags;
}

IPC_API(GetPlayerAnimationFlags, int(IPlayer& player))
{
	return openmp_scripting::GetPlayerAnimFlags(player);
}

IPC_API(IsPlayerInDriveByMode, bool(IPlayerVehicleData& data))
{
	return data.isInDriveByMode();
}

IPC_API(IsPlayerCuffed, bool(IPlayer& player))
{
	if (player_->getState() == PlayerState_OnFoot)
	{
		return player_->getAction() == SpecialAction_Cuffed;
	}
	else if (player_->getState() == PlayerState_Passenger)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player);
		if (data)
		{
			return data->isCuffed();
		}
	}
	return false;
}
*/