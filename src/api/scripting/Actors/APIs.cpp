#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Actor_Create, const nlohmann::json& params)
{
	IActorsComponent* component = OmpManager::Get()->actors;
	if (component)
	{
		int modelid = params["modelid"];
		float x = params["x"];
		float y = params["y"];
		float z = params["z"];
		float rotation = params["rot"];
		IActor* actor = component->create(modelid, { x, y ,z }, rotation);
		if (actor)
		{
			nlohmann::json ret;
			ret["ret_value"]["id"] = actor->getID();
			ret["ret_value"]["actor"] = reinterpret_cast<uintptr_t>(actor);
			return ret;
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Actor_Destroy, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	OmpManager::Get()->actors->release(actor->getID());
	return NO_DATA_SUCCESS_RETURN;
}


IPC_API(Actor_IsStreamedInFor, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return RETURN_VALUE(actor->isStreamedInForPlayer(*player));
}

IPC_API(Actor_SetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	actor->setVirtualWorld(params["virtualWorld"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Actor_GetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	return RETURN_VALUE(actor->getVirtualWorld());
}

IPC_API(Actor_ApplyAnimation, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, params["actor"], actor);
	const AnimationData animationData(params["delta"], params["loop"], params["lockX"],
		params["lockY"], params["freeze"], params["time"], params["library"], params["name"]);
	actor->applyAnimation(animationData);
	return NO_DATA_SUCCESS_RETURN;
}

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
	nlohmann::json ret;
	const Vector3& pos = actor->getPosition();
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
		return "{\"ret_value\":{\"error\":\"Pool for IActor is unavailable.\"}}"_json;

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
