#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Actor_Create, int model, float x, float y, float z, float rot)
{
	IActorsComponent* component = OmpManager::Get()->actors;
	if (component)
	{
		IActor* actor = component->create(model, { x, y ,z }, rot);
		if (actor)
		{
			nlohmann::json ret;
			auto id = actor->getID();
			auto ptr = reinterpret_cast<uintptr_t>(actor);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Actor_Destroy, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	OmpManager::Get()->actors->release(actor->getID());
	IPC_RETURN();
}

IPC_API(Actor_IsStreamedInFor, uintptr_t ptr, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, forPlayer);
	auto streamed = actor->isStreamedInForPlayer(*forPlayer);
	IPC_RETURN(bool streamed);
}

IPC_API(Actor_SetVirtualWorld, uintptr_t ptr, int vw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setVirtualWorld(vw);
	IPC_RETURN();
}

IPC_API(Actor_GetVirtualWorld, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	auto vw = actor->getVirtualWorld();
	IPC_RETURN(int vw);
}

IPC_API(Actor_ApplyAnimation, uintptr_t ptr, ConstStringRef name, ConstStringRef library, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	const AnimationData animationData(delta, loop, lockX, lockY, freeze, time, library, name);
	actor->applyAnimation(animationData);
	IPC_RETURN();
}

/*
IPC_API(Actor_ClearAnimations, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->clearAnimations();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_SetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	const Vector3& pos = actor->getPosition();

	nlohmann::json ret;
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(Actor_SetFacingAngle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setRotation(Vector3(0.0f, 0.0f, params["angle"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_GetFacingAngle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	return RETURN_VALUE(actor->getRotation().ToEuler().z);
}

IPC_API(Actor_SetHealth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setHealth(params["health"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_GetHealth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	return RETURN_VALUE(actor->getHealth());
}

IPC_API(Actor_SetInvulnerable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setInvulnerable(params["invulnerable"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_IsInvulnerable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	return RETURN_VALUE(actor->isInvulnerable());
}

IPC_API(Actor_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->actors == nullptr)
		return RETURN_ERROR("Pool for IActor is unavailable.");

	IActor* actor = reinterpret_cast<IActor*>(uintptr_t(params["actor"]));
	return RETURN_VALUE(actor != nullptr);
}

IPC_API(Actor_SetSkin, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setSkin(params["skin"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_GetSkin, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	return RETURN_VALUE(actor->getSkin());
}

IPC_API(Actor_GetAnimation, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	const AnimationData& anim = actor->getAnimation();

	nlohmann::json ret;
	ret["library"] = anim.lib.data();
	ret["name"] = anim.name.data();
	ret["delta"] = anim.delta;
	ret["loop"] = anim.loop;
	ret["lockX"] = anim.lockX;
	ret["lockY"] = anim.lockY;
	ret["freeze"] = anim.freeze;
	ret["time"] = anim.time;
	return RETURN_VALUE(ret);
}

IPC_API(Actor_GetSpawnInfo, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	const ActorSpawnData& spawnData = actor->getSpawnData();

	nlohmann::json ret;
	ret["x"] = spawnData.position.x;
	ret["y"] = spawnData.position.y;
	ret["z"] = spawnData.position.z;
	ret["angle"] = spawnData.facingAngle;
	ret["skin"] = spawnData.skin;
	return RETURN_VALUE(ret);
}
*/