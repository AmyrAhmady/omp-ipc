#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct ActorEvents : public ActorEventHandler, public Singleton<ActorEvents>
{
	void onPlayerGiveDamageActor(IPlayer& player, IActor& actor, float amount, unsigned weapon, BodyPart part) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["actor"] = uintptr_t(&actor);
		args["amount"] = amount;
		args["weapon"] = weapon;
		args["bodyPart"] = int(part);
		MessageSocket::ProcessEvent("playerGiveActorDamage", args);
	}

	void onActorStreamIn(IActor& actor, IPlayer& forPlayer) override
	{
		nlohmann::json args;
		args["actor"] = uintptr_t(&actor);
		args["forPlayer"] = uintptr_t(&forPlayer);
		MessageSocket::ProcessEvent("actorStreamIn", args);
	}

	void onActorStreamOut(IActor& actor, IPlayer& forPlayer) override
	{
		nlohmann::json args;
		args["actor"] = uintptr_t(&actor);
		args["forPlayer"] = uintptr_t(&forPlayer);
		MessageSocket::ProcessEvent("actorStreamOut", args);
	}
};
