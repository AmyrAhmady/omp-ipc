#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct ClassEvents : public ClassEventHandler, public Singleton<ClassEvents>
{
	void onPlayerRequestClass(IPlayer& player, unsigned int classId) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["classId"] = classId;
		MessageSocket::ProcessEvent("playerRequestClass", args);
	}
};
