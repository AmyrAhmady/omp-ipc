#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct MenuEvents : public MenuEventHandler, public Singleton<MenuEvents>
{
	void onPlayerSelectedMenuRow(IPlayer& player, MenuRow row) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["row"] = int(row);
		MessageSocket::ProcessEvent("playerSelectedMenuRow", args);
	}

	void onPlayerExitedMenu(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("playerExitedMenu", args);
	}
};