#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Checkpoint_Set, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		cp.setPosition({ params["x"], params["y"], params["z"] });
		cp.setRadius(params["radius"]);
		cp.enable();
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}

IPC_API(Checkpoint_Disable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		cp.disable();
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}

IPC_API(Checkpoint_IsPlayerIn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		if (cp.isEnabled())
		{
			return RETURN_VALUE(cp.isPlayerInside());
		}
	}
	return RETURN_VALUE(false);
}

IPC_API(RaceCheckpoint_Set, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		int type = params["type"];
		if (type >= 0 && type <= 8)
		{
			cp.setType(RaceCheckpointType(type));
			cp.setPosition({ params["x"], params["y"] , params["z"] });
			cp.setNextPosition({ params["nextX"], params["nextY"] , params["nextZ"] });
			cp.setRadius(params["radius"]);
			cp.enable();
			return NO_DATA_SUCCESS_RETURN;
		}
	}
	return RETURN_VALUE(false);
}

IPC_API(RaceCheckpoint_Disable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		cp.disable();
		return NO_DATA_SUCCESS_RETURN;
	}
	return RETURN_VALUE(false);
}

IPC_API(RaceCheckpoint_IsPlayerIn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		if (cp.getType() != RaceCheckpointType::RACE_NONE && cp.isEnabled())
		{
			return RETURN_VALUE(cp.isPlayerInside());
		}
	}
	return  RETURN_VALUE(false);
}

IPC_API(Checkpoint_IsActive, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player);
	if (playerData)
	{
		return RETURN_VALUE(playerData->getCheckpoint().isEnabled());
	}
	return  RETURN_VALUE(false);
}

IPC_API(Checkpoint_Get, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player);
	if (playerData)
	{
		const ICheckpointData& data = playerData->getCheckpoint();
		nlohmann::json ret;
		ret["x"] = data.getPosition().x;
		ret["y"] = data.getPosition().y;
		ret["z"] = data.getPosition().z;
		ret["radius"] = data.getRadius();
		return RETURN_VALUE(ret);
	}
	return  RETURN_VALUE(false);
}

IPC_API(RaceCheckpoint_IsActive, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player);
	if (playerData)
	{
		return RETURN_VALUE(playerData->getRaceCheckpoint().isEnabled());
	}
	return  RETURN_VALUE(false);
}

IPC_API(RaceCheckpoint_Get, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player);
	if (playerData)
	{
		const IRaceCheckpointData& data = playerData->getRaceCheckpoint();
		nlohmann::json ret;
		ret["x"] = data.getPosition().x;
		ret["y"] = data.getPosition().y;
		ret["z"] = data.getPosition().z;
		ret["nextX"] = data.getNextPosition().x;
		ret["nextY"] = data.getNextPosition().y;
		ret["nextZ"] = data.getNextPosition().z;
		ret["radius"] = data.getRadius();
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(false);
}
