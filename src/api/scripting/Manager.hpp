#pragma once
#include "../../utils/Singleton.hpp"
#include "../../message/Handler.hpp"
#include "sdk.hpp"
#include "component.hpp"
#include <nlohmann/json.hpp>
#include "Server/Components/Pickups/pickups.hpp"
#include "Server/Components/Objects/objects.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"
#include "Server/Components/Vehicles/vehicles.hpp"
#include "Server/Components/Checkpoints/checkpoints.hpp"
#include "Server/Components/Actors/actors.hpp"
#include "Server/Components/Classes/classes.hpp"
#include "Server/Components/Console/console.hpp"
#include "Server/Components/Timers/timers.hpp"
#include "Server/Components/CustomModels/custommodels.hpp"
#include "Server/Components/Dialogs/dialogs.hpp"
#include "Server/Components/Menus/menus.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/Recordings/recordings.hpp"
#include "Server/Components/TextDraws/textdraws.hpp"
#include "Server/Components/TextLabels/textlabels.hpp"

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

	ICore* core = nullptr;
	IPlayerPool* players = nullptr;
	IPickupsComponent* pickups = nullptr;
	IObjectsComponent* objects = nullptr;
	ITextLabelsComponent* textlabels = nullptr;
	IVehiclesComponent* vehicles = nullptr;
	IActorsComponent* actors = nullptr;
	IClassesComponent* classes = nullptr;
	IConsoleComponent* console = nullptr;
	ITimersComponent* timers = nullptr;
	ICustomModelsComponent* models = nullptr;
	IMenusComponent* menus = nullptr;
	ITextDrawsComponent* textdraws = nullptr;

private:
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
		return RETURN_ERROR("Pool for " STRINGIFY(#entity_type) " is unavailable."); \
	entity_type* entity_output = reinterpret_cast<entity_type*>(uintptr_t(entity_mem_addr)); \
	if(entity_output == nullptr) \
		return RETURN_ERROR("Invalid " STRINGIFY(#entity_type) " entity pointer.");

#define GET_PLAYER_POOL_ENTITY_CHECKED(player, pool_type, entity_type, entity_mem_addr, entity_output) \
	auto pool_instance = GetPlayerData<pool_type>(player); \
	if (pool_instance == nullptr) \
		return RETURN_ERROR("Pool for " STRINGIFY(#entity_type) " is unavailable."); \
	entity_type* entity_output = reinterpret_cast<entity_type*>(uintptr_t(entity_mem_addr)); \
	if (entity_output == nullptr) \
		return RETURN_ERROR("Invalid " STRINGIFY(#entity_type) " entity pointer.");

#define GET_PLAYER_DATA_CHECKED(player, entity_type, entity_output) \
	auto entity_output = GetPlayerData<entity_type>(player); \
	if (entity_output == nullptr) \
		return RETURN_ERROR("Data for " STRINGIFY(#entity_type) " is unavailable."); \
