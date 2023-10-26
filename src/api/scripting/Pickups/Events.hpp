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
	void onPickupStreamIn(IPickup& pickup, IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("pickupStreamIn", args);
	}
	void onPickupStreamOut(IPickup& pickup, IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("pickupStreamOut", args);
	}
};

struct PlayerPickupEvents : public PickupEventHandler, public Singleton<PlayerPickupEvents> 
{
	void onPlayerPickUpPlayerPickup(IPlayer& player, IPickup& pickup) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("playerPickUpPlayerPickup", args);
	}
	void onPlayerPickupStreamIn(IPickup& pickup, IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("playerPickupStreamIn", args);
	}
	void onPlayerPickupStreamOut(IPickup& pickup, IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["pickup"] = uintptr_t(&pickup);
		MessageSocket::ProcessEvent("playerPickupStreamOut", args);
	}
};
