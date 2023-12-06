#include "../Manager.hpp"

IPC_API(Checkpoint_Set, uintptr_t player, float x, float y, float z, float radius)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		cp.setPosition({ x, y, z });
		cp.setRadius(radius);
		cp.enable();
		IPC_RETURN();
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Checkpoint_Disable, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		cp.disable();
		IPC_RETURN();
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Checkpoint_IsPlayerIn, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		ICheckpointData& cp = playerCheckpointData->getCheckpoint();
		if (cp.isEnabled())
		{
			auto isIn = cp.isPlayerInside();
			IPC_RETURN(bool isIn);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Checkpoint_IsActive, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerData)
	{
		auto active = playerData->getCheckpoint().isEnabled();
		IPC_RETURN(bool active);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Checkpoint_Get, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerData)
	{
		const ICheckpointData& data = playerData->getCheckpoint();
		auto x = data.getPosition().x;
		auto y = data.getPosition().y;
		auto z = data.getPosition().z;
		auto radius = data.getRadius();
		IPC_RETURN(float x, float y, float z, float radius);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RaceCheckpoint_Set, uintptr_t player, int type, float x, float y, float z, float nextX, float nextY, float nextZ, float radius)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		if (type >= 0 && type <= 8)
		{
			cp.setType(RaceCheckpointType(type));
			cp.setPosition({ x, y, z });
			cp.setNextPosition({ nextX, nextY, nextZ });
			cp.setRadius(radius);
			cp.enable();
			IPC_RETURN();
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RaceCheckpoint_Disable, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		cp.disable();
		IPC_RETURN();
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RaceCheckpoint_IsPlayerIn, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerCheckpointData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerCheckpointData)
	{
		IRaceCheckpointData& cp = playerCheckpointData->getRaceCheckpoint();
		if (cp.getType() != RaceCheckpointType::RACE_NONE && cp.isEnabled())
		{
			auto isIn = cp.isPlayerInside();
			IPC_RETURN(bool isIn);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RaceCheckpoint_IsActive, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerData)
	{
		auto active = playerData->getCheckpoint().isEnabled();
		IPC_RETURN(bool active);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RaceCheckpoint_Get, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCheckpointData* playerData = queryExtension<IPlayerCheckpointData>(player_);
	if (playerData)
	{
		const IRaceCheckpointData& data = playerData->getRaceCheckpoint();
		auto x = data.getPosition().x;
		auto y = data.getPosition().y;
		auto z = data.getPosition().z;
		auto nextX = data.getNextPosition().x;
		auto nextY = data.getNextPosition().y;
		auto nextZ = data.getNextPosition().z;
		auto radius = data.getRadius();
		IPC_RETURN(float x, float y, float z, float nextX, float nextY, float nextZ, float radius);
	}
	return FUNCTION_FAIL_RETURN;
}
