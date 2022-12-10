#include <sdk.hpp>
#include "message/Socket.hpp"
#include "message/Handler.hpp"
#include "api/scripting/Manager.hpp"

struct OmpIPCComponent final : IComponent, CoreEventHandler {
	PROVIDE_UID(0x4eee85f136b79704);

	StringView componentName() const override
	{
		return "omp-ipc";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(0, 0, 0, 1);
	}

	void onLoad(ICore* c) override
	{
		// Cache core
		core = c;
		// TODO: This should be configurable
		MessageSocket::sockets.push_back(new MessageSocket("omp_node"));
		MessageHandlerPool::Get()->Init();

		core->getEventDispatcher().addEventHandler(this, EventPriority::EventPriority_FairlyHigh);
		c->printLn("omp-ipc component has been loaded");
	}

	void onTick(Microseconds elapsed, TimePoint now) override
	{
		MessageSocket::ProcessRequests(elapsed, now);
	}

	void onInit(IComponentList* components) override
	{
		OmpManager::Get()->Init(core, components);
		OmpManager::Get()->AddEvents();
	}

	void onReady() override
	{
		// Fire events here at earliest
	}

	void onFree(IComponent* component) override
	{

	}

	~OmpIPCComponent()
	{

	}

	void free() override
	{
		if (core)
		{
			OmpManager::Get()->RemoveEvents();
			core->getEventDispatcher().removeEventHandler(this);
		}
		delete this;
	}

	void reset() override
	{

	}

	ICore* core = nullptr;
};

COMPONENT_ENTRY_POINT()
{
	return new OmpIPCComponent();
}
