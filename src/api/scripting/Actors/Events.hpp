#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct ActorEvents : public ActorEventHandler, public Singleton<ActorEvents>
{
	void onPlayerGiveDamageActor(IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part) override
	{
		nlohmann::json args;
		args["ptr"] = uintptr_t(&player);
		args["actor_ptr"] = uintptr_t(&actor);
		args["amount"] = amount;
		args["weapon"] = weapon;
		args["bodyPart"] = int(part);
		MessageSocket::ProcessEvent("playerGiveActorDamage", args);
	}

	void onActorStreamIn(IActor& actor, IPlayer& forPlayer) override
	{
		nlohmann::json args;
		args["ptr"] = uintptr_t(&actor);
		args["player_ptr"] = uintptr_t(&forPlayer);
		MessageSocket::ProcessEvent("actorStreamIn", args);
	}

	void onActorStreamOut(IActor& actor, IPlayer& forPlayer) override
	{
		nlohmann::json args;
		args["ptr"] = uintptr_t(&actor);
		args["player_ptr"] = uintptr_t(&forPlayer);
		MessageSocket::ProcessEvent("actorStreamOut", args);
	}
};
