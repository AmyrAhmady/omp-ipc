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

IPC_API(Actor_ClearAnimations, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->clearAnimations();
	IPC_RETURN();
}

IPC_API(Actor_SetPos, uintptr_t ptr, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Actor_GetPos, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	const Vector3& pos = actor->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Actor_SetFacingAngle, uintptr_t ptr, float angle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setRotation(Vector3(0.0f, 0.0f, angle));
	IPC_RETURN();
}

IPC_API(Actor_GetFacingAngle, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	auto angle = actor->getRotation().ToEuler().z;
	IPC_RETURN(float angle);
}

IPC_API(Actor_SetHealth, uintptr_t ptr, float hp)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setHealth(hp);
	IPC_RETURN();
}

IPC_API(Actor_GetHealth, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	float hp = actor->getHealth();
	IPC_RETURN(float hp);
}

IPC_API(Actor_SetInvulnerable, uintptr_t ptr, bool toggle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setInvulnerable(toggle);
	IPC_RETURN();
}

IPC_API(Actor_IsInvulnerable, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	auto toggle = actor->isInvulnerable();
	IPC_RETURN(bool toggle);
}

IPC_API(Actor_IsValid, uintptr_t ptr)
{
	if (OmpManager::Get()->actors == nullptr)
		return RETURN_ERROR("Pool for IActor is unavailable.");

	IActor* actor = reinterpret_cast<IActor*>(ptr);
	auto valid = actor != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Actor_SetSkin, uintptr_t ptr, int skin)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	actor->setSkin(skin);
	IPC_RETURN();
}

IPC_API(Actor_GetSkin, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	auto skin = actor->getSkin();
	IPC_RETURN(bool skin);
}

IPC_API(Actor_GetAnimation, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	const AnimationData& anim = actor->getAnimation();

	nlohmann::json ret;
	auto library = anim.lib.data();
	auto name = anim.name.data();
	auto delta = anim.delta;
	auto loop = anim.loop;
	auto lockX = anim.lockX;
	auto lockY = anim.lockY;
	auto freeze = anim.freeze;
	auto time = anim.time;
	IPC_RETURN(ConstStringRef library, ConstStringRef name, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time);
}

IPC_API(Actor_GetSpawnInfo, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, ptr, actor);
	const ActorSpawnData& spawnData = actor->getSpawnData();

	nlohmann::json ret;
	auto x = spawnData.position.x;
	auto y = spawnData.position.y;
	auto z = spawnData.position.z;
	auto angle = spawnData.facingAngle;
	auto skin = spawnData.skin;
	IPC_RETURN(float x, float y, float z, float angle, float skin);
}
