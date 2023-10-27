#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct ObjectEvents : public ObjectEventHandler, public Singleton<ObjectEvents>
{
	void onObjectSelected(IPlayer& player, IObject& object, int model, Vector3 position) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["type"] = 1;
		args["object"] = uintptr_t(&object);
		args["model"] = model;
		args["fX"] = position.x;
		args["fY"] = position.y;
		args["fZ"] = position.z;
		MessageSocket::ProcessEvent("objectSelected", args);
	}

	void onObjectEdited(IPlayer& player, IObject& object, ObjectEditResponse response, Vector3 offset, Vector3 rotation) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["playerObject"] = 0;
		args["object"] = uintptr_t(&object);
		args["response"] = int(response);
		args["fX"] = offset.x;
		args["fY"] = offset.y;
		args["fZ"] = offset.z;
		args["rotationX"] = rotation.x;
		args["rotationY"] = rotation.y;
		args["rotationZ"] = rotation.z;
		MessageSocket::ProcessEvent("objectEdited", args);
	}

	void onPlayerAttachedObjectEdited(IPlayer& player, int index, bool saved, const ObjectAttachmentSlotData& data) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["response"] = saved;
		args["index"] = index;
		args["modelId"] = data.model;
		args["boneId"] = data.bone;
		args["fOffsetX"] = data.offset.x;
		args["fOffsetY"] = data.offset.y;
		args["fOffsetZ"] = data.offset.z;
		args["rotationX"] = data.rotation.x;
		args["rotationY"] = data.rotation.y;
		args["rotationZ"] = data.rotation.z;
		args["scaleX"] = data.scale.x;
		args["scaleY"] = data.scale.y;
		args["scaleZ"] = data.scale.z;
		MessageSocket::ProcessEvent("playerAttachedObjectEdited", args);
	}

	void onMoved(IObject& object) override
	{
		nlohmann::json args;
		args["object"] = uintptr_t(&object);
		MessageSocket::ProcessEvent("objectMoved", args);
	}
};

struct PlayerObjectEvents : public ObjectEventHandler, public Singleton<PlayerObjectEvents>
{
	void onPlayerObjectSelected(IPlayer& player, IObject& object, int model, Vector3 position) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["type"] = 2;
		args["object"] = uintptr_t(&object);
		args["model"] = model;
		args["fX"] = position.x;
		args["fY"] = position.y;
		args["fZ"] = position.z;
		MessageSocket::ProcessEvent("playerObjectSelected", args);
	}

	void onPlayerObjectEdited(IPlayer& player, IObject& object, ObjectEditResponse response, Vector3 offset, Vector3 rotation) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["playerObject"] = 1;
		args["object"] = uintptr_t(&object);
		args["response"] = int(response);
		args["fX"] = offset.x;
		args["fY"] = offset.y;
		args["fZ"] = offset.z;
		args["rotationX"] = rotation.x;
		args["rotationY"] = rotation.y;
		args["rotationZ"] = rotation.z;
		MessageSocket::ProcessEvent("playerObjectEdited", args);
	}

	void onPlayerObjectMoved(IPlayer& player, IPlayerObject& object) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["object"] = uintptr_t(&object);
		MessageSocket::ProcessEvent("playerObjectMoved", args);
	}
};
