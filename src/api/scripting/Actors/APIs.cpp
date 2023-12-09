#include "../Manager.hpp"

IPC_API(Actor_Create, int model, float x, float y, float z, float rot)
{
	IActorsComponent* component = OmpManager::Get()->actors;
	if (component)
	{
		IActor* actor = component->create(model, { x, y, z }, rot);
		if (actor)
		{
			auto id = actor->getID();
			auto ptr = reinterpret_cast<uintptr_t>(actor);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Actor_Destroy, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	OmpManager::Get()->actors->release(actor_->getID());
	IPC_RETURN();
}

IPC_API(Actor_IsStreamedInFor, uintptr_t actor, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto streamed = actor_->isStreamedInForPlayer(*player_);
	IPC_RETURN(bool streamed);
}

IPC_API(Actor_SetVirtualWorld, uintptr_t actor, int vw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setVirtualWorld(vw);
	IPC_RETURN();
}

IPC_API(Actor_GetVirtualWorld, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	auto vw = actor_->getVirtualWorld();
	IPC_RETURN(int vw);
}

IPC_API(Actor_ApplyAnimation, uintptr_t actor, ConstStringRef name, ConstStringRef library, float delta, bool loop, bool lockX, bool lockY, bool freeze, int time)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	const AnimationData animationData(delta, loop, lockX, lockY, freeze, time, library, name);
	actor_->applyAnimation(animationData);
	IPC_RETURN();
}

IPC_API(Actor_ClearAnimations, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->clearAnimations();
	IPC_RETURN();
}

IPC_API(Actor_SetPos, uintptr_t actor, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Actor_GetPos, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	const Vector3& pos = actor_->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Actor_SetFacingAngle, uintptr_t actor, float angle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setRotation(Vector3(0.0f, 0.0f, angle));
	IPC_RETURN();
}

IPC_API(Actor_GetFacingAngle, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	auto angle = actor_->getRotation().ToEuler().z;
	IPC_RETURN(float angle);
}

IPC_API(Actor_SetHealth, uintptr_t actor, float hp)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setHealth(hp);
	IPC_RETURN();
}

IPC_API(Actor_GetHealth, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	float hp = actor_->getHealth();
	IPC_RETURN(float hp);
}

IPC_API(Actor_SetInvulnerable, uintptr_t actor, bool toggle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setInvulnerable(toggle);
	IPC_RETURN();
}

IPC_API(Actor_IsInvulnerable, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	auto toggle = actor_->isInvulnerable();
	IPC_RETURN(bool toggle);
}

IPC_API(Actor_IsValid, uintptr_t actor)
{
	if (OmpManager::Get()->actors == nullptr)
		return RETURN_ERROR("Pool for IActor is unavailable.");

	IActor* actor_ = reinterpret_cast<IActor*>(actor);
	auto valid = actor_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Actor_SetSkin, uintptr_t actor, int skin)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	actor_->setSkin(skin);
	IPC_RETURN();
}

IPC_API(Actor_GetSkin, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	auto skin = actor_->getSkin();
	IPC_RETURN(bool skin);
}

IPC_API(Actor_GetAnimation, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	const AnimationData& anim = actor_->getAnimation();

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

IPC_API(Actor_GetSpawnInfo, uintptr_t actor)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->actors, IActor, actor, actor_);
	const ActorSpawnData& spawnData = actor_->getSpawnData();

	auto x = spawnData.position.x;
	auto y = spawnData.position.y;
	auto z = spawnData.position.z;
	auto angle = spawnData.facingAngle;
	auto skin = spawnData.skin;
	IPC_RETURN(float x, float y, float z, float angle, float skin);
}
