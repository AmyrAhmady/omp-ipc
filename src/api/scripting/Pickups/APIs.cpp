#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Pickup_Create, const nlohmann::json& params)
{
	IPickupsComponent* component = OmpManager::Get()->pickups;
	if (component)
	{
		IPickup* pickup = component->create(params["model"], params["type"],
			{ params["x"], params["y"], params["z"] }, params["virtualWorld"], false);
		if (pickup)
		{
			return RETURN_VALUE(pickup->getID());
		}
	}
	return RETURN_VALUE(INVALID_PICKUP_ID);
}

IPC_API(Pickup_CreateStatic, const nlohmann::json& params)
{
	IPickupsComponent* component = OmpManager::Get()->pickups;
	if (component)
	{
		IPickup* pickup = component->create(params["model"], params["type"],
			{ params["x"], params["y"], params["z"] }, params["virtualWorld"], true);
		if (pickup)
		{
			return NO_DATA_SUCCESS_RETURN;
		}
	}
	return RETURN_VALUE(false);
}

IPC_API(Pickup_Destroy, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	OmpManager::Get()->pickups->release(pickup->getID());
	return true;
}

IPC_API(Pickup_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->pickups == nullptr)
		return RETURN_ERROR("Pool for IActor is unavailable.");

	IPickup* pickup = reinterpret_cast<IPickup*>(uintptr_t(params["pickup"]));
	return RETURN_VALUE(pickup != nullptr);
}

IPC_API(Pickup_IsStreamedIn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return pickup->isStreamedInForPlayer(*player);
}

IPC_API(Pickup_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	auto pos = pickup->getPosition();
	nlohmann::json ret;
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(Pickup_GetModel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	return RETURN_VALUE(pickup->getModel());
}

IPC_API(Pickup_GetType, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	return RETURN_VALUE(pickup->getType());
}

IPC_API(Pickup_GetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	return RETURN_VALUE(pickup->getVirtualWorld());
}

IPC_API(Pickup_SetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	bool update = params["update"];
	if (update)
	{
		pickup->setPosition({ params["x"], params["y"], params["z"] });
	}
	else
	{
		pickup->setPositionNoUpdate({ params["x"], params["y"], params["z"] });
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_SetModel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	pickup->setModel(params["model"], params["update"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_SetType, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	pickup->setType(params["type"], params["update"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_SetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	pickup->setVirtualWorld(params["virtualWorld"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_ShowForPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	pickup->setPickupHiddenForPlayer(*player, false);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_HideForPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	pickup->setPickupHiddenForPlayer(*player, true);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Pickup_IsHiddenForPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->pickups, IPickup, params["pickup"], pickup);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(pickup->isPickupHiddenForPlayer(*player));
}
