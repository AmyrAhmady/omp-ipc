#pragma once
#include "../utils/Singleton.hpp"
#include "sdk.hpp"
#include "component.hpp"
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "Server/Components/Actors/actors.hpp"

#define UNDEFINED_FAILED_RETURN "{\"ret_value\": null}"_json

class OmpManager : public Singleton<OmpManager>
{
public:
	/// Store open.mp components
	void Init(ICore* c, IComponentList* clist)
	{
		core = c;
		componentList = clist;
		players = &core->getPlayers();

		actors = GetComponent<IActorsComponent>();
		objects = GetComponent<IObjectsComponent>();
		pickups = GetComponent<IPickupsComponent>();
		textlabels = GetComponent<ITextLabelsComponent>();
		vehicles = GetComponent<IVehiclesComponent>();
	}

	/// Get open.mp core instance
	ICore* GetCore()
	{
		return core;
	}

	/// Get player pool
	IPlayerPool* GetPlayers()
	{
		return players;
	}

	/// Get an open.mp component
	template<typename ComponentType>
	ComponentType* GetComponent()
	{
		return componentList->queryComponent<ComponentType>();
	}

	/// Get pickups component
	IPickupsComponent* GetPickups()
	{
		return pickups;
	}

	/// Get objects component
	IObjectsComponent* GetObjects()
	{
		return objects;
	}

	/// Get vehicles component
	IVehiclesComponent* GetVehicles()
	{
		return vehicles;
	}

	/// Get textlabels component
	ITextLabelsComponent* GetTextLabels()
	{
		return textlabels;
	}

	/// Get actors component
	IActorsComponent* GetActors()
	{
		return actors;
	}

private:
	ICore* core = nullptr;
	IComponentList* componentList = nullptr;
	IPlayerPool* players = nullptr;
	IPickupsComponent* pickups = nullptr;
	IObjectsComponent* objects = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	IActorsComponent* actors = nullptr;
};

/// Get player from players pool
inline IPlayer* GetPlayer(int playerid)
{
	IPlayerPool* pool = OmpManager::Get()->GetPlayers();
	if (pool == nullptr)
	{
		return nullptr;
	}

	return pool->get(playerid);
}

/// Get player from players pool
template<typename PlayerDataType>
inline PlayerDataType* GetPlayerData(int playerid)
{
	IPlayer* player = GetPlayer(playerid);
	if (player == nullptr)
	{
		return nullptr;
	}

	return queryExtension<PlayerDataType>(*player);
}

/// Get player entity using provided player id and entity id
template<typename PlayerEntityPoolType, typename EntityType>
inline EntityType* GetPlayerEntity(int playerid, int entity_id)
{
	PlayerEntityPoolType* pool = GetPlayerData<PlayerEntityPoolType>(playerid);
	if (pool == nullptr)
	{
		return nullptr;
	}

	return pool->get(entity_id);
}

/// Get entity using provided entity id
template<typename EntityType, typename EntityPoolType>
inline EntityType* GetEntity(int entity_id)
{
	EntityPoolType* pool = OmpManager::Get()->GetComponent<EntityPoolType>();
	if (pool == nullptr)
	{
		return nullptr;
	}

	return pool->get(entity_id);
}

/// Just a dummy function and it returns nullptr, overloads will do the job
template<typename EntityType>
inline EntityType* GetEntity(int entity_id)
{
	return nullptr;
}

template<>
inline IPickup* GetEntity<IPickup>(int entity_id)
{
	IPickupsComponent* pickups = OmpManager::Get()->GetPickups();
	if (pickups == nullptr)
	{
		return nullptr;
	}

	return pickups->get(entity_id);
}

template<>
inline IVehicle* GetEntity<IVehicle>(int entity_id)
{
	IVehiclesComponent* vehicles = OmpManager::Get()->GetVehicles();
	if (vehicles == nullptr)
	{
		return nullptr;
	}

	return vehicles->get(entity_id);
}

template<>
inline IActor* GetEntity<IActor>(int entity_id)
{
	IActorsComponent* actors = OmpManager::Get()->GetActors();
	if (actors == nullptr)
	{
		return nullptr;
	}

	return actors->get(entity_id);
}

template<>
inline IObject* GetEntity<IObject>(int entity_id)
{
	IObjectsComponent* objects = OmpManager::Get()->GetObjects();
	if (objects == nullptr)
	{
		return nullptr;
	}

	return objects->get(entity_id);
}

/// Get player using provided player id, return fail_ret if not available
#define GET_PLAYER_CHECKED(player_output, playerid, fail_ret) \
	IPlayer* player_output = GetPlayer(playerid); \
	if(player_output == nullptr) return fail_ret;

/// Get player object, return fail_ret if not available
#define GET_PLAYER_OBJECT_CHECKED(object_output, playerid, objectid, fail_ret) \
	IPlayerObject* object_output = GetPlayerEntity<IPlayerObjectData, IPlayerObject>(playerid, objectid); \
	if(object_output == nullptr) return fail_ret;

/// Get player textlabels, return fail_ret if not available
#define GET_PLAYER_TEXT_LABEL_CHECKED(text_label_output, playerid, textlabelid, fail_ret) \
	IPlayerTextLabel* text_label_output = GetPlayerEntity<IPlayerTextLabelData, IPlayerTextLabel>(playerid, textlabelid); \
	if(text_label_output == nullptr) return fail_ret;

#define GET_ENTITY_CHECKED(entity_output, entity_type, entity_id, fail_ret) \
	entity_type* entity_output = GetEntity<entity_type>(entity_id); \
	if(entity_output == nullptr) return fail_ret;
