#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct PickupEvents : public PickupEventHandler, public Singleton<PickupEvents> 
{
	void onPlayerPickUpPickup(IPlayer& player, IPickup& pickup) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("playerPickUpPickup", args);
	}
};
