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

IPC_API(Player_SetWantedLevel, uintptr_t player, int level)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setWantedLevel(level);
	IPC_RETURN();
}

IPC_API(Player_SetWeather, uintptr_t player, int weather)
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

IPC_API(Player_SetTeam, uintptr_t player, int team)
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

IPC_API(Player_GetDistanceFromPoint, uintptr_t player, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Vector3 playerCoords = player_->getPosition();
	float distance = glm::distance(playerCoords, { x, y, z });
	IPC_RETURN(float distance);
}

IPC_API(Player_GetInterior, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int interior = player_->getInterior();
	IPC_RETURN(int interior);
}

IPC_API(Player_SetPos, uintptr_t player, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Player_GetPos, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto pos = player_->getPosition();
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Player_GetVirtualWorld, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int vw = player_->getVirtualWorld();
	IPC_RETURN(int vw);
}

IPC_API(Player_IsNPC, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto bot = player_->isBot();
	IPC_RETURN(bool bot);
}

IPC_API(Player_IsStreamedIn, uintptr_t player, uintptr_t other)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, other, other_);
	bool streamed = player_->isStreamedInForPlayer(*other_);
	IPC_RETURN(bool streamed);
}

IPC_API(Player_PlaySound, uintptr_t player, int sound, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->playSound(sound, { x, y, z });
	IPC_RETURN();
}

IPC_API(Player_SpectatePlayer, uintptr_t player, uintptr_t target, int mode)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, target, target_);
	player_->spectatePlayer(*target_, PlayerSpectateMode(mode));
	IPC_RETURN();
}

IPC_API(Player_SpectateVehicle, uintptr_t player, uintptr_t target, int mode)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, target, target_);
	player_->spectateVehicle(*target_, PlayerSpectateMode(mode));
	IPC_RETURN();
}

IPC_API(Player_SetVirtualWorld, uintptr_t player, int vw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setVirtualWorld(vw);
	IPC_RETURN();
}

IPC_API(Player_SetWorldBounds, uintptr_t player, float xMax, float xMin, float yMax, float yMin)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Vector4 coords = { xMax, xMin, yMax, yMin };
	player_->setWorldBounds(coords);
	IPC_RETURN();
}

IPC_API(Player_ClearWorldBounds, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setWorldBounds(Vector4(MAX_WORLD_BOUNDS, MIN_WORLD_BOUNDS, MAX_WORLD_BOUNDS, MIN_WORLD_BOUNDS));
	IPC_RETURN();
}

IPC_API(Player_GetWorldBounds, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto bounds = player_->getWorldBounds();
	float xmax = bounds.x;
	float xmin = bounds.y;
	float ymax = bounds.z;
	float ymin = bounds.w;
	IPC_RETURN(float xmax, float xmin, float ymax, float ymin);
}

IPC_API(ClearAnimations, uintptr_t player, int syncType)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	// TODO: This must be fixed on client side
	// At the moment ClearAnimations flushes all tasks applied to player
	// Including driving, siting in vehicle, shooting, jumping, or any sort of a task
	// And it doesn't just clear applied animations, in order to keep it compatible with
	// Current samp scripts without requiring a change, we call IPlayer::clearTasks temporarily.
	player_->clearTasks(PlayerAnimationSyncType(syncType));
	IPC_RETURN();
}

IPC_API(Player_GetLastShotVectors, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerBulletData data = player_->getBulletData();
	auto origin = data.origin;
	auto hitPos = data.hitPos;

	float origin_x = origin.x;
	float origin_y = origin.y;
	float origin_z = origin.z;

	float hit_x = hitPos.x;
	float hit_y = hitPos.y;
	float hit_z = hitPos.z;

	IPC_RETURN(float origin_x, float origin_y, float origin_z, float hit_x, float hit_y, float hit_z);
}

IPC_API(Player_GetCameraTargetPlayer, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto target = uintptr_t(player_->getCameraTargetPlayer());
	IPC_RETURN(uintptr_t target);
}

IPC_API(Player_GetCameraTargetActor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto target = uintptr_t(player_->getCameraTargetActor());
	IPC_RETURN(uintptr_t target);
}

IPC_API(Player_GetCameraTargetObject, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto target = uintptr_t(player_->getCameraTargetObject());
	IPC_RETURN(uintptr_t target);
}

IPC_API(Player_GetCameraTargetVehicle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto target = uintptr_t(player_->getCameraTargetVehicle());
	IPC_RETURN(uintptr_t target);
}

IPC_API(Player_PutInVehicle, uintptr_t player, uintptr_t vehicle, int seat)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->putPlayer(*player_, seat);
	IPC_RETURN();
}

IPC_API(Player_RemoveBuilding, uintptr_t player, int model, float x, float y, float z, float radius)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->removeDefaultObjects(model, { x, y, z }, radius);
	IPC_RETURN();
}

IPC_API(Player_GetBuildingsRemoved, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool count = player_->getDefaultObjectsRemoved();
	IPC_RETURN(bool count);
}

IPC_API(Player_RemoveFromVehicle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->removeFromVehicle(false);
	IPC_RETURN();
}

IPC_API(Player_RemoveMapIcon, uintptr_t player, int icon)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->unsetMapIcon(icon);
	IPC_RETURN();
}

IPC_API(Player_SetMapIcon, uintptr_t player, int iconID, float x, float y, float z, int type, uint32_t colour, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setMapIcon(iconID, { x, y, z }, type, Colour::FromRGBA(colour), MapIconStyle(style));
	IPC_RETURN();
}

IPC_API(Player_ResetWeapons, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->resetWeapons();
	IPC_RETURN();
}

IPC_API(Player_SetAmmo, uintptr_t player, uint8_t id, uint32_t ammo)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	WeaponSlotData data;
	data.id = id;
	data.ammo = ammo;
	player_->setWeaponAmmo(data);
	IPC_RETURN();
}

IPC_API(Player_SetArmedWeapon, uintptr_t player, uint8_t weapon)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setArmedWeapon(weapon);
	IPC_RETURN();
}

IPC_API(Player_SetChatBubble, uintptr_t player, ConstStringRef text, uint32_t colour, float drawdistance, int expiretime)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setChatBubble(text, Colour::FromRGBA(colour), drawdistance, std::chrono::milliseconds(expiretime));
	IPC_RETURN();
}

IPC_API(Player_SetPosFindZ, uintptr_t player, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setPositionFindZ({ x, y, z });
	IPC_RETURN();
}

IPC_API(Player_SetSkillLevel, uintptr_t player, uint8_t weapon, int level)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setSkillLevel(PlayerWeaponSkill(weapon), level);
	IPC_RETURN();
}

IPC_API(Player_SetSpecialAction, uintptr_t player, uint32_t action)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setAction(PlayerSpecialAction(action));
	IPC_RETURN();
}

IPC_API(Player_ShowNameTagForPlayer, uintptr_t player, uintptr_t other, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, other, other_);
	player_->toggleOtherNameTag(other_, enable);
	IPC_RETURN();
}

IPC_API(Player_ToggleControllable, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setControllable(enable);
	IPC_RETURN();
}

IPC_API(Player_ToggleSpectating, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setSpectating(enable);
	IPC_RETURN();
}

IPC_API(Player_ApplyAnimation, uintptr_t player, ConstStringRef animlib, ConstStringRef animname, float delta, bool loop, bool lockX, bool lockY, bool freeze, uint32_t time, int sync)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	ConstStringRef AnimationData animationData(delta, loop, lockX, lockY, freeze, time, animlib, animname);
	player_->applyAnimation(animationData, PlayerAnimationSyncType(sync));
	IPC_RETURN();
}

IPC_API(Player_GetAnimationName, int index, ConstStringRef lib, ConstStringRef name)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Pair<StringView, StringView> anim = splitAnimationNames(index);
	ConstStringRef animlib = anim.first;
	ConstStringRef animname = anim.second;
	IPC_RETURN(ConstStringRef animlib, ConstStringRef animname);
}

IPC_API(Player_EditAttachedObject, uintptr_t data, int index)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerObjectData, data, data_);
	data_->editAttachedObject(index);
	IPC_RETURN();
}

IPC_API(Player_EnableCameraTarget, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useCameraTargeting(enable);
	IPC_RETURN();
}

IPC_API(Player_EnableStuntBonus, uintptr_t player, bool enable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->useStuntBonuses(enable);
	IPC_RETURN();
}

IPC_API(All_EnableStuntBonus, bool enable)
{
	OmpManager::Get()->core->useStuntBonuses(enable);
	IPC_RETURN();
}

IPC_API(Player_GetPlayerAmmo, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int ammo = player_->getArmedWeaponAmmo();
	IPC_RETURN(int ammo);
}

IPC_API(Player_GetAnimationIndex, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int id = player_->getAnimationData().ID;
	IPC_RETURN(int id);
}

IPC_API(Player_GetFacingAngle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GTAQuat quat = player_->getRotation();
	float angle = quat.ToEuler().z;
	IPC_RETURN(float angle);
}

IPC_API(Player_GetIp, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PeerNetworkData data = player_->getNetworkData();
	if (!data.networkID.address.ipv6)
	{
		PeerAddress::AddressString addressString;
		if (PeerAddress::ToString(data.networkID.address, addressString))
		{
			// Scope-allocated string, copy it
			ConstStringRef ip = String(StringView(addressString));
			IPC_RETURN(ConstStringRef ip);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Player_GetSpecialAction, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int action = player_->getAction();
	IPC_RETURN(int action);
}

IPC_API(Player_GetVehicleID, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerVehicleData, data, data_);
	IVehicle* vehicle = data_->getVehicle();
	if (vehicle)
	{
		int id = vehicle->getID();
		IPC_RETURN(int id);
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetVehicleSeat, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerVehicleData, data, data_);
	int seat = data_->getSeat();
	IPC_RETURN(int seat);
}

IPC_API(Player_GetWeaponData, uintptr_t player, int slot)
{
	if (slot < 0 || slot >= MAX_WEAPON_SLOTS)
	{
		return NO_DATA_SUCCESS_RETURN;
	}
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	const WeaponSlotData& weapon = player_->getWeaponSlot(slot);
	int weaponid = weapon.id;
	int ammo = weapon.ammo;
	IPC_RETURN(int weaponid, int ammo);
}

IPC_API(Player_GetWeaponState, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int state = player_->getAimData().weaponState;
	IPC_RETURN(int state);
}

IPC_API(Player_InterpolateCameraPos, uintptr_t player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->interpolateCameraPosition({ from_x, from_y, from_z }, { to_x, to_y, to_z }, time, PlayerCameraCutType(cut));
	IPC_RETURN();
}

IPC_API(Player_InterpolateCameraLookAt, uintptr_t player, float from_x, float from_y, float from_z, float to_x, float to_y, float to_z, int time, int cut)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->interpolateCameraLookAt({ from_x, from_y, from_z }, { to_x, to_y, to_z }, time, PlayerCameraCutType(cut));
	IPC_RETURN();
}

IPC_API(Player_IsPlayerAttachedObjectSlotUsed, uintptr_t data, int index)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerObjectData, data, data_);
	int ret = data_->hasAttachedObject(index);
	IPC_RETURN(int ret);
}

IPC_API(Player_AttachCameraToObject, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	player_->attachCameraToObject(object_);
	IPC_RETURN();
}

IPC_API(Player_AttachCameraToPlayerObject, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IPlayerObject, object, object_);
	player_->attachCameraToObject(object_);
	IPC_RETURN();
}

IPC_API(Player_GetCameraAspectRatio, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	float ratio = player_->getAimData().aspectRatio;
	IPC_RETURN(float ratio);
}

IPC_API(Player_GetCameraFrontVector, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto vector = player_->getAimData().camFrontVector;
	float x = vector.x;
	float y = vector.y;
	float z = vector.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Player_GetCameraMode, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int cameraMode = player_->getAimData().camMode;
	IPC_RETURN(int cameraMode);
}

IPC_API(Player_GetKeys, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	const PlayerKeyData& keyData = player_->getKeyData();
	int keys = keyData.keys;
	int updown = keyData.upDown;
	int leftright = keyData.leftRight;
	IPC_RETURN(int keys, int updown, int leftright);
}

IPC_API(Player_GetSurfingVehicleID, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Vehicle)
	{
		IVehiclesComponent* vehicles = OmpManager::Get()->vehicles;
		if (vehicles && vehicles->get(data.ID))
		{
			int id = data.ID;
			IPC_RETURN(int id);
		}
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetSurfingObjectID, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerSurfingData data = player_->getSurfingData();
	if (player_->getState() == PlayerState_OnFoot && data.type == PlayerSurfingData::Type::Object)
	{
		IObjectsComponent* objects = OmpManager::Get()->objects;
		if (objects && objects->get(data.ID))
		{
			int id = data.ID;
			IPC_RETURN(int id);
		}
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetTargetPlayer, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayer* target = player_->getTargetPlayer();
	if (target)
	{
		int target = target->getID();
		IPC_RETURN(int target);
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_GetTargetActor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IActor* target = player_->getTargetActor();
	if (target)
	{
		int target = target->getID();
		IPC_RETURN(int target);
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_IsInVehicle, uintptr_t data, uintptr_t targetVehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerVehicleData, data, data_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, targetVehicle, targetVehicle_);
	IVehicle* vehicle = data_->getVehicle();
	bool ret = bool(vehicle == &targetVehicle_);
	IPC_RETURN(bool ret);
}

IPC_API(Player_IsInAnyVehicle, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerVehicleData, data, data_);
	IVehicle* vehicle = data_->getVehicle();
	bool ret = bool(vehicle != nullptr);
	IPC_RETURN(bool ret);
}

IPC_API(Player_IsInRangeOfPoint, uintptr_t player, float range, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool ret = bool(range >= glm::distance(player_->getPosition(), { x, y, z }));
	IPC_RETURN(bool ret);
}

IPC_API(Player_PlayCrimeReport, uintptr_t player, uintptr_t suspect, int crime)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, suspect, suspect_);
	bool ret = bool(player_->playerCrimeReport(suspect_, crime));
	IPC_RETURN(bool ret);
}

IPC_API(Player_RemoveAttachedObject, uintptr_t data, int index)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerObjectData, data, data_);
	data_->removeAttachedObject(index);
	IPC_RETURN();
}

IPC_API(Player_SetAttachedObject, uintptr_t data, int index, int modelid, int bone, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ, uint32_t materialcolor1, uint32_t materialcolor2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerObjectData, data, data_);
	ObjectAttachmentSlotData attachment;
	attachment.model = modelid;
	attachment.bone = bone;
	attachment.offset = { offsetX, offsetY, offsetZ };
	attachment.rotation = { rotationX, rotationY, rotationZ };
	attachment.scale = { scaleX, scaleY, scaleZ };
	attachment.colour1 = Colour::FromARGB(materialcolor1);
	attachment.colour2 = Colour::FromARGB(materialcolor2);
	data_->setAttachedObject(index, attachment);
	IPC_RETURN();
}

IPC_API(Player_GetAttachedObject, uintptr_t data, int index)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerObjectData, data, data_);
	ObjectAttachmentSlotData attachment = data_->getAttachedObject(index);
	int modelid = attachment.model;
	int bone = attachment.bone;
	float offsetX = attachment.offset.x;
	float offsetY = attachment.offset.y;
	float offsetZ = attachment.offset.z;
	float rotationX = attachment.rotation.x;
	float rotationY = attachment.rotation.y;
	float rotationZ = attachment.rotation.z;
	float scaleX = attachment.scale.x;
	float scaleY = attachment.scale.y;
	float scaleZ = attachment.scale.z;
	int materialcolor1 = attachment.colour1.ARGB();
	int materialcolor2 = attachment.colour2.ARGB();
	IPC_RETURN(int modelid, int bone, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ, int materialcolor1, int materialcolor2);
}

IPC_API(Player_SetFacingAngle, uintptr_t player, float angle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Vector3 rotation = player_->getRotation().ToEuler();
	rotation.z = angle;
	player_->setRotation(rotation);
	IPC_RETURN();
}

IPC_API(Player_SetMarkerForPlayer, uintptr_t player, uintptr_t other, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, other, other_);
	player_->setOtherColour(other_, Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(Player_GetMarkerForPlayer, uintptr_t player, uintptr_t other)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, other, other_);
	Colour colour;
	bool hasPlayerSpecificColour = player_->getOtherColour(other, colour);
	if (!hasPlayerSpecificColour)
	{
		colour = other.getColour();
	}
	uint32_t rgba = colour.RGBA();
	IPC_RETURN(rgba);
}

IPC_API(Player_AllowTeleport, uintptr_t player, bool allow)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->allowTeleport(allow);
	IPC_RETURN();
}

IPC_API(Player_IsTeleportAllowed, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool allowed = bool(player_->isTeleportAllowed());
	IPC_RETURN(bool allowed);
}

IPC_API(Player_DisableRemoteVehicleCollisions, uintptr_t player, bool disable)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setRemoteVehicleCollisions(!disable);
	IPC_RETURN();
}

IPC_API(Player_GetCameraZoom, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	float cameraZoom = player_->getAimData().camZoom;
	IPC_RETURN(float cameraZoom);
}

IPC_API(Player_SelectTextDraw, uintptr_t data, uint32_t hoverColour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerTextDrawData, data, data_);
	data_->beginSelection(Colour::FromRGBA(hoverColour));
	IPC_RETURN();
}

IPC_API(Player_CancelSelectTextDraw, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerTextDrawData, data, data_);
	data_->endSelection();
	IPC_RETURN();
}

IPC_API(Player_SendClientCheck, uintptr_t player, int actionType, int address, int offset, int count)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->sendClientCheck(actionType, address, offset, count);
	IPC_RETURN();
}

IPC_API(Player_Spawn, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->spawn();
	IPC_RETURN();
}

IPC_API(Player_GPCI, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	ConstStringRef serial = player_->getSerial().data();
	int len = serial.length();
	IPC_RETURN(ConstStringRef serial, int len);
}

IPC_API(Player_IsAdmin, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerConsoleData, data, data_);
	bool access = data_->hasConsoleAccess();
	IPC_RETURN(bool access);
}

IPC_API(Player_Kick, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->kick();
	IPC_RETURN();
}

IPC_API(Player_ShowGameText, uintptr_t player, ConstStringRef text, int time, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	if (text.empty())
	{
		return NO_DATA_SUCCESS_RETURN;
	}
	player_->sendGameText(text, Milliseconds(time), style);
	IPC_RETURN();
}

IPC_API(Player_HideGameText, uintptr_t player, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->hideGameText(style);
	IPC_RETURN();
}

IPC_API(Player_HasGameText, uintptr_t player, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool has = player_->hasGameText(style);
	IPC_RETURN(bool has);
}

IPC_API(Player_GetGameText, uintptr_t player, int style)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	Milliseconds mt;
	Milliseconds mr;
	StringView ms;
	if (player_->getGameText(style, ms, mt, mr))
	{
		ConstStringRef message = ms;
		int time = (int)mt.count();
		int remaining = (int)mr.count();
		IPC_RETURN(ConstStringRef message, int time, int remaining);
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Player_Ban, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->ban();
	IPC_RETURN();
}

IPC_API(Player_BanEx, uintptr_t player, ConstStringRef reason)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->ban(reason);
	IPC_RETURN();
}

IPC_API(Player_SendDeathMessage, uintptr_t player, uintptr_t killer, uintptr_t killee, int weapon)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, killee, killee_);
	if (killee_)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, killer, killer_);
		player_->sendDeathMessage(killee_, killer_, weapon);
	}
	else
	{
		player_->sendEmptyDeathMessage();
	}
	IPC_RETURN();
}

IPC_API(Player_SendMessageToPlayer, uintptr_t player, uintptr_t sender, ConstStringRef message)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, sender, sender_);
	player_->sendChatMessage(sender_, message);
	IPC_RETURN();
}

IPC_API(Player_GetVersion, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	ConstStringRef version = player_->getClientVersionName().data();
	int len = version.length();
	IPC_RETURN(ConstStringRef version, int len);
}

IPC_API(Player_GetSkillLevel, uintptr_t player, int skill)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto skills = player_->getSkillLevels();
	if (skill >= 11 || skill < 0)
	{
		return NO_DATA_SUCCESS_RETURN;
	}
	int ret = skills[skill];
	IPC_RETURN(int ret);
}

IPC_API(Player_GetZAim, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	float z = player_->getAimData().aimZ;
	IPC_RETURN(float z);
}

IPC_API(Player_GetSurfingOffsets, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	const PlayerSurfingData& data = player_->getSurfingData();
	float offsetX = 0.0;
	float offsetY = 0.0;
	float offsetZ = 0.0;
	if (data.type != PlayerSurfingData::Type::None)
	{
		offsetX = data.offset.x;
		offsetY = data.offset.y;
		offsetZ = data.offset.z;
	}
	IPC_RETURN(float offsetX, float offsetY, float offsetZ);
}

IPC_API(Player_GetRotationQuat, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	glm::quat rotQuat = player_->getRotation().q;

	// In samp or YSF, GetPlayerRotationQuat declaration is like this:
	// GetPlayerRotationQuat(playerid, &Float:w, &Float:x = 0.0, &Float:y = 0.0, &Float:z = 0.0);
	// Meaning first output arg is W and not X; Vector4's first member is X and it is used in many other places,
	// We can't just simply change ParamCast for Vector4 just because one function doesn't follow it.

	float x = rotQuat.w;
	float y = rotQuat.x;
	float z = rotQuat.y;
	float w = rotQuat.z;
	IPC_RETURN(float x, float y, float z, float w);
}

IPC_API(Player_GetPlayerSpectateID, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int spectateId = player_->getSpectateData().spectateID;
	IPC_RETURN(int spectateId);
}

IPC_API(Player_GetSpectateType, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	int spectateType = int(player_->getSpectateData().type);
	IPC_RETURN(int spectateType);
}

IPC_API(Player_GetRawIp, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	ConstStringRef ip = player_->getNetworkData().networkID.address.v4;
	IPC_RETURN(ConstStringRef ip);
}

IPC_API(Player_SetGravity, uintptr_t player, float gravity)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->setGravity(gravity);
	IPC_RETURN();
}

IPC_API(Player_GetGravity, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	float gravity = player_->getGravity();
	IPC_RETURN(float gravity);
}

IPC_API(Player_SetAdmin, uintptr_t data, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerConsoleData, data, data_);
	data_->setConsoleAccessibility(set);
	IPC_RETURN();
}

IPC_API(Player_IsSpawned, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerState state = player_->getState();
	bool spawned = false;
	switch (state)
	{
		case PlayerState_OnFoot:
		case PlayerState_Driver:
		case PlayerState_Passenger:
		case PlayerState_Spawned:
		{
			spawned = true;
		}
		default:
			spawned = false;
	}
	IPC_RETURN(bool spawned);
}

IPC_API(Player_IsControllable, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool controllable = bool(player_->getControllable());
	IPC_RETURN(bool controllable);
}

IPC_API(Player_IsCameraTargetEnabled, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool enabled = bool(player_->hasCameraTargeting());
	IPC_RETURN(bool enabled);
}

IPC_API(Player_ToggleGhostMode, uintptr_t player, bool toggle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->toggleGhostMode(toggle);
	IPC_RETURN();
}

IPC_API(Player_GetGhostMode, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool enabled = bool(player_->isGhostModeEnabled());
	IPC_RETURN(bool enabled);
}

IPC_API(Player_AllowWeapons, uintptr_t player, bool allow)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	player_->allowWeapons(allow);
	IPC_RETURN();
}

IPC_API(Player_AreWeaponsAllowed, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool allowed = bool(player_->areWeaponsAllowed());
	IPC_RETURN(bool allowed);
}

IPC_API(Player_IsPlayerUsingOfficialClient, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool ret = bool(player_->isUsingOfficialClient());
	IPC_RETURN(bool ret);
}

IPC_API(Player_GetAnimationFlags, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PlayerAnimationData data = player_->getAnimationData();
	int flags = data.flags;
	IPC_RETURN(int flags);
}

IPC_API(Player_IsInDriveByMode, uintptr_t data)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayerVehicleData, data, data_);
	bool driveby = bool(data_->isInDriveByMode());
	IPC_RETURN(bool driveby);
}

IPC_API(Player_IsCuffed, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool cuffed = false;
	if (player_->getState() == PlayerState_OnFoot)
	{
		cuffed = bool(player_->getAction() == SpecialAction_Cuffed);
	}
	else if (player_->getState() == PlayerState_Passenger)
	{
		IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
		if (data)
		{
			cuffed = bool(data->isCuffed());
		}
	}
	IPC_RETURN(bool cuffed);
}
