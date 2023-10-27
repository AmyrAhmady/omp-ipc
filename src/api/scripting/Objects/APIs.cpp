#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Object_Create, const nlohmann::json& params)
{
	IObjectsComponent* component = OmpManager::Get()->objects;
	if (component)
	{
		IObject* object = component->create(
			params["modelId"], 
			{ params["x"], params["y"], params["z"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] },
			params["drawDistance"]);

		if (object)
		{
			return RETURN_VALUE(object->getID());
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Object_Destroy, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	OmpManager::Get()->objects->release(object->getID());
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_AttachToVehicle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["parent"], vehicle);
	if (vehicle)
	{
		object->attachToVehicle(
			*vehicle, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] });
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_AttachToObject, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["parent"], objAttachedTo);
	if (objAttachedTo)
	{
		object->attachToObject(
			*objAttachedTo, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] }, 
			params["syncRotation"]);
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_AttachToPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["parent"], playerAttachedTo);
	if (playerAttachedTo)
	{
		object->attachToPlayer(
			*playerAttachedTo, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] });
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_SetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->setPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	nlohmann::json ret;
	const Vector3& pos = object->getPosition();
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(Object_SetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->setRotation({ params["rotationX"], params["rotationY"], params["rotationZ"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_GetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	nlohmann::json ret;
	const Vector3& rot = object->getRotation().ToEuler();
	ret["rotationX"] = rot.x;
	ret["rotationY"] = rot.y;
	ret["rotationZ"] = rot.z;
	return RETURN_VALUE(ret);
}

IPC_API(Object_GetModel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	if (!object) {
		return RETURN_VALUE(INVALID_OBJECT_MODEL_ID);
	}
	return RETURN_VALUE(object->getModel());
}

IPC_API(Object_SetNoCameraCollision, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->setCameraCollision(false);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->objects == nullptr)
		return "{\"ret_value\":{\"error\":\"Pool for IObject is unavailable.\"}}"_json;

	IObject* object = reinterpret_cast<IObject*>(uintptr_t(params["object"]));
	return RETURN_VALUE(object != nullptr);
}

IPC_API(Object_Move, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);

	ObjectMoveData data;
	data.targetPos = { params["targetX"], params["targetY"], params["targetZ"] };
	data.targetRot = { params["rotationX"], params["rotationY"], params["rotationZ"] };
	data.speed = params["speed"];

	object->move(data);

	float estimatedTime = (glm::length(data.targetPos - object->getPosition()) / data.speed) * 1000.0f;
	return RETURN_VALUE(static_cast<int>(estimatedTime));
}

IPC_API(Object_Stop, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->stop();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_IsMoving, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	return RETURN_VALUE(object->isMoving());
}

IPC_API(Object_BeginEditing, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);

	if (!playerObjectData)
	{
		return NO_DATA_SUCCESS_RETURN;
	}

	playerObjectData->beginEditing(object);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_BeginSelecting, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);

	if (!playerObjectData)
	{
		return NO_DATA_SUCCESS_RETURN;
	}

	playerObjectData->beginSelecting();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_EndEditing, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);
	
	if (!playerObjectData)
	{
		return NO_DATA_SUCCESS_RETURN;
	}

	playerObjectData->endEditing();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_SetMaterial, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->setMaterial(
		params["materialIndex"], 
		params["modelId"], 
		params["textureLibrary"],
		params["textureName"],
		Colour::FromARGB(params["materialColour"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_SetMaterialText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	object->setMaterialText(
		params["materialIndex"], 
		params["text"], 
		ObjectMaterialSize(params["materialSize"]), 
		params["fontface"], 
		params["fontsize"], 
		params["bold"], 
		Colour::FromARGB(params["fontColour"]), 
		Colour::FromARGB(params["backgroundColour"]), 
		ObjectMaterialTextAlign(params["textalignment"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Object_SetDefaultCameraCollision, const nlohmann::json& params)
{
	IObjectsComponent* component = OmpManager::Get()->objects;
	if (component)
	{
		bool disable = params["disable"];
		component->setDefaultCameraCollision(!disable);
		return NO_DATA_SUCCESS_RETURN;
	}

	return RETURN_VALUE(false);
}

IPC_API(Object_GetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	return RETURN_VALUE(object->getDrawDistance());
}

IPC_API(Object_GetMoveSpeed, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	return RETURN_VALUE(object->getMovingData().speed);
}

IPC_API(Object_GetMovingTargetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	nlohmann::json ret;
	const ObjectMoveData& data = object->getMovingData();
	ret["targetX"] = data.targetPos.x;
	ret["targetY"] = data.targetPos.y;
	ret["targetZ"] = data.targetPos.z;
	return RETURN_VALUE(ret);
}

IPC_API(Object_GetMovingTargetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	nlohmann::json ret;
	const ObjectMoveData& data = object->getMovingData();
	ret["rotationX"] = data.targetRot.x;
	ret["rotationY"] = data.targetRot.y;
	ret["rotationZ"] = data.targetRot.z;
	return RETURN_VALUE(ret);
}

IPC_API(Object_GetAttachedData, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	
	const ObjectAttachmentData data = object->getAttachmentData();
	int parentVehicle = INVALID_VEHICLE_ID;
	int parentObject = INVALID_OBJECT_ID;
	int parentPlayer = INVALID_PLAYER_ID;

	if (data.type == ObjectAttachmentData::Type::Object)
	{
		parentObject = data.ID;
	}
	else if (data.type == ObjectAttachmentData::Type::Player)
	{
		parentPlayer = data.ID;
	}
	else if (data.type == ObjectAttachmentData::Type::Vehicle)
	{
		parentVehicle = data.ID;
	}

	nlohmann::json ret;
	ret["parentVehicle"] = parentVehicle;
	ret["parentObject"] = parentObject;
	ret["parentPlayer"] = parentPlayer;
	return RETURN_VALUE(ret);
}

IPC_API(Object_GetAttachedOffset, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	nlohmann::json ret;
	const ObjectAttachmentData data = object->getAttachmentData();
	ret["offsetX"] = data.offset.x;
	ret["offsetY"] = data.offset.y;
	ret["offsetZ"] = data.offset.z;
	ret["rotationX"] = data.rotation.x;
	ret["rotationY"] = data.rotation.y;
	ret["rotationZ"] = data.rotation.z;
	return RETURN_VALUE(ret);
}

IPC_API(Object_GetSyncRotation, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	return RETURN_VALUE(object->getAttachmentData().syncRotation);
}

IPC_API(Object_IsMaterialSlotUsed, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		return RETURN_VALUE(data->used);
	}
	return RETURN_VALUE(result);
}

IPC_API(Object_GetMaterial, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		nlohmann::json ret;
		ret["modelId"] = data->model;
		ret["textureLibrary"] = data->textOrTXD;
		ret["textureName"] = data->fontOrTexture;
		ret["materialColour"] = data->materialColour.ARGB();
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(result);
}

IPC_API(Object_GetMaterialText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		nlohmann::json ret;
		ret["text"] = data->textOrTXD;
		ret["materialSize"] = data->materialSize;
		ret["fontFace"] = data->fontOrTexture;
		ret["fontSize"] = data->fontSize;
		ret["bold"] = data->bold;
		ret["fontColour"] = data->fontColour.ARGB();
		ret["backgroundColour"] = data->backgroundColour.ARGB();
		ret["textAlignment"] = data->alignment;
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(result);
}

IPC_API(Object_HasCameraCollision, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, params["object"], object);
	return RETURN_VALUE(!object->getCameraCollision());
}

IPC_API(Object_GetType, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);

	if (playerObjectData->get(params["objectId"]) != nullptr)
	{
		return RETURN_VALUE(2); // Player object type
	}

	IObjectsComponent* component = OmpManager::Get()->objects;
	if (component)
	{
		if (component->get(params["objectId"]) != nullptr)
		{
			return RETURN_VALUE(1); // Global object type
		}
	}

	return UNDEFINED_FAILED_RETURN;
}

/*
	Per-Player Objects
*/

IPC_API(PlayerObject_Create, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);
	
	IPlayerObject* object = playerObjectData->create(
		params["modelId"], 
		{ params["x"], params["y"], params["z"] }, 
		{ params["rotationX"], params["rotationY"], params["rotationZ"] },
		params["drawDistance"]);

	if (object)
	{
		return RETURN_VALUE(object->getID());
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(PlayerObject_Destroy, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);
	
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);

	playerObjectData->release(object->getID());
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_AttachToVehicle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["parent"], vehicle);

	if (vehicle)
	{
		object->attachToVehicle(
			*vehicle, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] });
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_AttachToPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["parent"], playerAttachedTo);

	if (playerAttachedTo)
	{
		object->attachToPlayer(
			*playerAttachedTo, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] });
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_AttachToObject, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["parent"], attachedTo);
	if (attachedTo)
	{
		object->attachToObject(
			*attachedTo, 
			{ params["offsetX"], params["offsetY"], params["offsetZ"] }, 
			{ params["rotationX"], params["rotationY"], params["rotationZ"] });
	}
	else
	{
		object->resetAttachment();
	}
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_SetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->setPosition({ params["x"], params["y"], params["z"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	nlohmann::json ret;
	const Vector3& pos = object->getPosition();
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_SetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->setRotation({ params["rotationX"], params["rotationY"], params["rotationZ"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_GetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	nlohmann::json ret;
	const Vector3& rot = object->getRotation().ToEuler();
	ret["rotationX"] = rot.x;
	ret["rotationY"] = rot.y;
	ret["rotationZ"] = rot.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_GetModel, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	if (!object) {
		return RETURN_VALUE(INVALID_OBJECT_MODEL_ID);
	}
	return RETURN_VALUE(object->getModel());
}

IPC_API(PlayerObject_SetNoCameraCollision, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->setCameraCollision(false);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->playerobjects == nullptr)
		return "{\"ret_value\":{\"error\":\"Pool for IPlayerObject is unavailable.\"}}"_json;

	IPlayerObject* object = reinterpret_cast<IPlayerObject*>(uintptr_t(params["object"]));
	return RETURN_VALUE(object != nullptr);
}

IPC_API(PlayerObject_Move, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);

	ObjectMoveData data;
	data.targetPos = { params["targetX"], params["targetY"], params["targetZ"] };
	data.targetRot = { params["rotationX"], params["rotationY"], params["rotationZ"] };
	data.speed = params["speed"];

	object->move(data);

	float estimatedTime = (glm::length(data.targetPos - object->getPosition()) / data.speed) * 1000.0f;
	return RETURN_VALUE(static_cast<int>(estimatedTime));
}

IPC_API(PlayerObject_Stop, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->stop();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_IsMoving, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	return RETURN_VALUE(object->isMoving());
}

IPC_API(PlayerObject_BeginEditing, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerObjectData* playerObjectData = queryExtension<IPlayerObjectData>(player);
	playerObjectData->beginEditing(object);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_SetMaterial, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->setMaterial(
		params["materialIndex"], 
		params["modelId"], 
		params["textureLibrary"],
		params["textureName"],
		Colour::FromARGB(params["materialColour"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_SetMaterialText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	object->setMaterialText(
		params["materialIndex"], 
		params["text"], 
		ObjectMaterialSize(params["materialSize"]), 
		params["fontface"], 
		params["fontsize"], 
		params["bold"], 
		Colour::FromARGB(params["fontColour"]), 
		Colour::FromARGB(params["backgroundColour"]), 
		ObjectMaterialTextAlign(params["textalignment"]));
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerObject_GetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	return RETURN_VALUE(object->getDrawDistance());
}

IPC_API(PlayerObject_GetMoveSpeed, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	return RETURN_VALUE(object->getMovingData().speed);
}

IPC_API(PlayerObject_GetMovingTargetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	nlohmann::json ret;
	const ObjectMoveData& data = object->getMovingData();
	ret["targetX"] = data.targetPos.x;
	ret["targetY"] = data.targetPos.y;
	ret["targetZ"] = data.targetPos.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_GetMovingTargetRot, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	nlohmann::json ret;
	const ObjectMoveData& data = object->getMovingData();
	ret["rotationX"] = data.targetRot.x;
	ret["rotationY"] = data.targetRot.y;
	ret["rotationZ"] = data.targetRot.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_GetAttachedData, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	
	const ObjectAttachmentData data = object->getAttachmentData();
	int parentVehicle = INVALID_VEHICLE_ID;
	int parentObject = INVALID_OBJECT_ID;
	int parentPlayer = INVALID_PLAYER_ID;

	if (data.type == ObjectAttachmentData::Type::Object)
	{
		parentObject = data.ID;
	}
	else if (data.type == ObjectAttachmentData::Type::Player)
	{
		parentPlayer = data.ID;
	}
	else if (data.type == ObjectAttachmentData::Type::Vehicle)
	{
		parentVehicle = data.ID;
	}

	nlohmann::json ret;
	ret["parentVehicle"] = parentVehicle;
	ret["parentObject"] = parentObject;
	ret["parentPlayer"] = parentPlayer;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_GetAttachedOffset, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	nlohmann::json ret;
	const ObjectAttachmentData data = object->getAttachmentData();
	ret["offsetX"] = data.offset.x;
	ret["offsetY"] = data.offset.y;
	ret["offsetZ"] = data.offset.z;
	ret["rotationX"] = data.rotation.x;
	ret["rotationY"] = data.rotation.y;
	ret["rotationZ"] = data.rotation.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerObject_GetSyncRotation, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	return RETURN_VALUE(object->getAttachmentData().syncRotation);
}

IPC_API(PlayerObject_IsMaterialSlotUsed, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		return RETURN_VALUE(data->used);
	}
	return RETURN_VALUE(result);
}

IPC_API(PlayerObject_GetMaterial, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		nlohmann::json ret;
		ret["modelId"] = data->model;
		ret["textureLibrary"] = data->textOrTXD;
		ret["textureName"] = data->fontOrTexture;
		ret["materialColour"] = data->materialColour.ARGB();
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(result);
}

IPC_API(PlayerObject_GetMaterialText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	const ObjectMaterialData* data = nullptr;
	bool result = object->getMaterialData(params["materialIndex"], data);
	if (result)
	{
		nlohmann::json ret;
		ret["text"] = data->textOrTXD;
		ret["materialSize"] = data->materialSize;
		ret["fontFace"] = data->fontOrTexture;
		ret["fontSize"] = data->fontSize;
		ret["bold"] = data->bold;
		ret["fontColour"] = data->fontColour.ARGB();
		ret["backgroundColour"] = data->backgroundColour.ARGB();
		ret["textAlignment"] = data->alignment;
		return RETURN_VALUE(ret);
	}
	return RETURN_VALUE(result);
}

IPC_API(PlayerObject_HasCameraCollision, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playerobjects, IPlayerObject, params["object"], object);
	return RETURN_VALUE(!object->getCameraCollision());
}

IPC_API(PlayerObject_GetPlayerSurfingID, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	const PlayerSurfingData& data = player->getSurfingData();
	if (data.type == PlayerSurfingData::Type::PlayerObject)
	{
		return RETURN_VALUE(data.ID);
	}
	else
	{
		return RETURN_VALUE(INVALID_OBJECT_ID);
	}
}

IPC_API(PlayerObject_GetPlayerCameraTarget, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IObject* object = player->getCameraTargetObject();
	if (object)
	{
		return RETURN_VALUE(object->getID());
	}
	else
	{
		return RETURN_VALUE(INVALID_OBJECT_ID);
	}
}
