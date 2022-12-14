#pragma once
#include "../../utils/Singleton.hpp"
#include "sdk.hpp"
#include "component.hpp"
#include <nlohmann/json.hpp>
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "Server/Components/Actors/actors.hpp"

#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

class OmpManager : public Singleton<OmpManager>
{
public:
	/// Store open.mp components
	void Init(ICore* c, IComponentList* clist);

	// Add event handlers to components' event dispatchers
	void AddEvents();

	// Remove event handlers from components' event dispatchers
	void RemoveEvents();

	/// Get open.mp core instance
	ICore* GetCore()
	{
		return core;
	}

	/// Get an open.mp component
	template<typename ComponentType>
	ComponentType* GetComponent()
	{
		return componentList->queryComponent<ComponentType>();
	}

	IPlayerPool* players = nullptr;
	IPickupsComponent* pickups = nullptr;
	IObjectsComponent* objects = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	IActorsComponent* actors = nullptr;

private:
	ICore* core = nullptr;
	IComponentList* componentList = nullptr;
};

/// Get player from players pool
template<typename PlayerDataType>
inline PlayerDataType* GetPlayerData(IPlayer* player)
{
	if (player == nullptr)
	{
		return nullptr;
	}
	return queryExtension<PlayerDataType>(*player);
}

/// Get player using provided player id, return fail_ret if not available
#define GET_POOL_ENTITY_CHECKED(pool_instance, entity_type, entity_mem_addr, entity_output) \
	if(pool_instance == nullptr) \
		return "{\"ret_value\":{\"error\":\"Pool for " STRINGIFY(#entity_type) " is unavailable.\"}}"_json; \
	entity_type* entity_output = reinterpret_cast<entity_type*>(uintptr_t(entity_mem_addr)); \
	if(entity_output == nullptr) \
		return "{\"ret_value\":{\"error\":\"Invalid " STRINGIFY(#entity_type) " entity pointer " STRINGIFY(#entity_mem_addr) ".\"}}"_json;
