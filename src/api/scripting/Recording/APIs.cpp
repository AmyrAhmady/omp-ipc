#include "../Manager.hpp"

IPC_API(Recording_Start, uintptr_t player, int type, ConstStringRef file)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerRecordingData* recording = queryExtension<IPlayerRecordingData>(player_);
	if (recording)
	{
		recording->start(PlayerRecordingType(type), file);
	}
	IPC_RETURN();
}

IPC_API(Recording_Stop, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerRecordingData* recording = queryExtension<IPlayerRecordingData>(player_);
	if (recording)
	{
		recording->stop();
	}
	IPC_RETURN();
}
