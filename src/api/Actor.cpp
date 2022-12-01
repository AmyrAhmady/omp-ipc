#include "../message/Handler.hpp"
#include "./Manager.hpp"

IPC_API(createActor, const nlohmann::json& params)
{
	IActorsComponent* component = OmpManager::Get()->GetActors();
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
			ret["ret_value"]["ptr"] = reinterpret_cast<uintptr_t>(actor);
			return ret;
		}
	}
	return UNDEFINED_FAILED_RETURN;
}
