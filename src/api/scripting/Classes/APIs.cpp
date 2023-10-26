#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Class_Add, const nlohmann::json& params)
{
	IClassesComponent* component = OmpManager::Get()->classes;
	if (component)
	{
		WeaponSlots slots = {
			WeaponSlotData { params["weapon1"], params["ammo1"] },
			WeaponSlotData { params["weapon2"], params["ammo2"] },
			WeaponSlotData { params["weapon3"], params["ammo3"] }
		};

		IClass* _class = component->create(
			params["skin"], 
			TEAM_NONE, 
			{params["spawnX"], params["spawnY"], params["spawnZ"]}, 
			params["angle"], 
			slots);

		if (_class)
		{
			nlohmann::json ret;
			ret["ret_value"]["id"] = _class->getID();
			ret["ret_value"]["class"] = reinterpret_cast<uintptr_t>(_class);
			return ret;
			// return RETURN_VALUE(_class->getID());
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Class_AddEx, const nlohmann::json& params)
{
	IClassesComponent* component = OmpManager::Get()->classes;
	if (component)
	{
		WeaponSlots slots = {
			WeaponSlotData { params["weapon1"], params["ammo1"] },
			WeaponSlotData { params["weapon2"], params["ammo2"] },
			WeaponSlotData { params["weapon3"], params["ammo3"] }
		};

		IClass* _class = component->create(
			params["skin"], 
			params["team"], 
			{params["spawnX"], params["spawnY"], params["spawnZ"]}, 
			params["angle"], 
			slots);

		if (_class)
		{
			nlohmann::json ret;
			ret["ret_value"]["id"] = _class->getID();
			ret["ret_value"]["class"] = reinterpret_cast<uintptr_t>(_class);
			return ret;
			// return RETURN_VALUE(_class->getID());
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Class_SetSpawnInfo, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerClassData* classData = queryExtension<IPlayerClassData>(player);
	if (classData)
	{
		WeaponSlots slots = {
			WeaponSlotData { params["weapon1"], params["ammo1"] },
			WeaponSlotData { params["weapon2"], params["ammo2"] },
			WeaponSlotData { params["weapon3"], params["ammo3"] }
		};

		classData->setSpawnInfo(
				PlayerClass(
					params["skin"], 
					params["team"], 
					{params["spawnX"], params["spawnY"], params["spawnZ"]}, 
					params["angle"], 
					slots
				)
			);
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}

IPC_API(Class_GetSpawnInfo, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerClassData* playerData = queryExtension<IPlayerClassData>(player);
	if (playerData)
	{
		const PlayerClass& data = playerData->getClass();

		nlohmann::json ret;
		ret["team"] = data.team;
		ret["skin"] = data.skin;
		ret["spawnPosition"] = data.spawn;
		ret["angle"] = data.angle;
		ret["weapon1"] = data.weapons[0].id;
		ret["ammo1"] = data.weapons[0].ammo;
		ret["weapon2"] = data.weapons[1].id;
		ret["ammo2"] = data.weapons[1].ammo;
		ret["weapon3"] = data.weapons[2].id;
		ret["ammo3"] = data.weapons[2].ammo;
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(false);
}

IPC_API(Class_GetAvailable, const nlohmann::json& params)
{
	IClassesComponent* component = OmpManager::Get()->classes;
	if (component)
	{
		return RETURN_VALUE(component->count());
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Class_Get, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->classes, IClass, params["class"], class_);
	const PlayerClass& data = class_.getClass();

	nlohmann::json ret;
	ret["team"] = data.team;
	ret["skin"] = data.skin;
	ret["spawnPosition"] = data.spawn;
	ret["angle"] = data.angle;
	ret["weapon1"] = data.weapons[0].id;
	ret["ammo1"] = data.weapons[0].ammo;
	ret["weapon2"] = data.weapons[1].id;
	ret["ammo2"] = data.weapons[1].ammo;
	ret["weapon3"] = data.weapons[2].id;
	ret["ammo3"] = data.weapons[2].ammo;
	return RETURN_VALUE(ret);
}

IPC_API(Class_Edit, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->classes, IClass, params["class"], class_);

	WeaponSlots weapons;
	weapons[0].id = params["weapon1"];
	weapons[0].ammo = params["ammo1"];
	weapons[1].id = params["weapon2"];
	weapons[1].ammo = params["ammo2"];
	weapons[2].id = params["weapon3"];
	weapons[2].ammo = params["ammo3"];

	PlayerClass data = PlayerClass(
		params["skin"], 
		params["team"], 
		{params["spawnX"], params["spawnY"], params["spawnZ"]}, 
		params["angle"], 
		weapons);

	class_.setClass(data);
	return NO_DATA_SUCCESS_RETURN;
}
