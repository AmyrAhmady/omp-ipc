#include "Manager.hpp"
#include "Actors/Events.hpp"
#include "Players/Events.hpp"

#define ADD_EVENT_HANDLER(component, event_instance) \
	if (component) \
	{ \
		component->getEventDispatcher().addEventHandler(event_instance); \
	}

#define REMOVE_EVENT_HANDLER(component, event_instance) \
	if (component) \
	{ \
		component->getEventDispatcher().removeEventHandler(event_instance); \
	}

void OmpManager::Init(ICore* c, IComponentList* clist)
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

void OmpManager::AddEvents()
{
	ADD_EVENT_HANDLER(actors, ActorEvents::Get());
	ADD_EVENT_HANDLER(players, PlayerEvents::Get());
}

void OmpManager::RemoveEvents()
{
	REMOVE_EVENT_HANDLER(actors, ActorEvents::Get());
	REMOVE_EVENT_HANDLER(players, PlayerEvents::Get());
}
