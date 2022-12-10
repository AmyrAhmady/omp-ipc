#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct CheckpointEvents : public PlayerCheckpointEventHandler, public Singleton<CheckpointEvents>
{
	void onPlayerEnterCheckpoint(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("playerEnterCheckpoint", args);
	}

	void onPlayerLeaveCheckpoint(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("playerLeaveCheckpoint", args);
	}

	void onPlayerEnterRaceCheckpoint(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("playerEnterRaceCheckpoint", args);
	}

	void onPlayerLeaveRaceCheckpoint(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("playerLeaveRaceCheckpoint", args);
	}
};
