#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Class_Add, uint8_t team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3)
{
	IClassesComponent* component = OmpManager::Get()->classes;
	if (component)
	{

		WeaponSlots slots = {
			WeaponSlotData { weapon1, ammo1 },
			WeaponSlotData { weapon2, ammo2 },
			WeaponSlotData { weapon3, ammo3 }
		};

		IClass* _class = component->create(skin, team, { x, y, z }, angle, slots);

		if (_class)
		{
			auto id = _class->getID();
			auto ptr = reinterpret_cast<uintptr_t>(_class);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}

	return FUNCTION_FAIL_RETURN;
}

IPC_API(Player_SetSpawnInfo, uintptr_t player, int team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerClassData* classData = queryExtension<IPlayerClassData>(player_);
	if (classData)
	{
		WeaponSlots slots = {
			WeaponSlotData { weapon1, ammo1 },
			WeaponSlotData { weapon2, ammo2 },
			WeaponSlotData { weapon3, ammo3 }
		};

		classData->setSpawnInfo(PlayerClass(skin, team, { x, y, z }, angle, slots));
		IPC_RETURN();
	}
	IPC_RETURN();
}

IPC_API(Player_GetSpawnInfo, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerClassData* playerData = queryExtension<IPlayerClassData>(player_);
	if (playerData)
	{
		const PlayerClass& data = playerData->getClass();
		auto team = data.team;
		auto skin = data.skin;
		auto x = data.spawn.x;
		auto y = data.spawn.y;
		auto z = data.spawn.z;
		auto angle = data.angle;
		auto weapon1 = data.weapons[0].id;
		auto ammo1 = data.weapons[0].ammo;
		auto weapon2 = data.weapons[1].id;
		auto ammo2 = data.weapons[1].ammo;
		auto weapon3 = data.weapons[2].id;
		auto ammo3 = data.weapons[2].ammo;
		IPC_RETURN(int team, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t ammo1, uint8_t weapon2, uint32_t ammo2, uint8_t weapon3, uint32_t ammo3);
	}
	IPC_RETURN();
}

IPC_API(Class_GetAvailableClasses)
{
	IClassesComponent* component = OmpManager::Get()->classes;
	if (component)
	{
		auto count = component->count();
		IPC_RETURN(int count);
	}
	IPC_RETURN();
}

IPC_API(Class_GetData, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->classes, IClass, ptr, class_);
	const PlayerClass& data = class_->getClass();
	auto teamid = data.team;
	auto skin = data.skin;
	auto x = data.spawn.x;
	auto y = data.spawn.y;
	auto z = data.spawn.z;
	auto angle = data.angle;
	auto weapon1 = data.weapons[0].id;
	auto weapon1_ammo = data.weapons[0].ammo;
	auto weapon2 = data.weapons[1].id;
	auto weapon2_ammo = data.weapons[1].ammo;
	auto weapon3 = data.weapons[2].id;
	auto weapon3_ammo = data.weapons[2].ammo;
	IPC_RETURN(int teamid, int skin, float x, float y, float z, float angle, uint8_t weapon1, uint32_t weapon1_ammo, uint8_t weapon2, uint32_t weapon2_ammo, uint8_t weapon3, uint32_t weapon3_ammo);
}

IPC_API(Class_Edit, uintptr_t ptr, int teamid, int skin, float x, float y, float z, float angle, int weapon1, int weapon1_ammo, int weapon2, int weapon2_ammo, int weapon3, int weapon3_ammo)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->classes, IClass, ptr, class_);
	WeaponSlots weapons;
	weapons[0].id = weapon1;
	weapons[0].ammo = weapon1_ammo;
	weapons[1].id = weapon2;
	weapons[1].ammo = weapon2_ammo;
	weapons[2].id = weapon3;
	weapons[2].ammo = weapon3_ammo;
	PlayerClass data = PlayerClass(skin, teamid, { x, y, z }, angle, weapons);
	class_->setClass(data);
	IPC_RETURN();
}
