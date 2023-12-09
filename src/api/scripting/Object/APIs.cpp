#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Object_Create, int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance)
{
	IObjectsComponent* component = OmpManager::Get()->objects;
	if (component)
	{
		IObject* object = component->create(modelid, { x, y, z }, { rotationX, rotationY, rotationZ }, drawDistance);
		if (object)
		{
			auto id = object->getID();
			auto ptr = reinterpret_cast<uintptr_t>(object);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Object_Destroy, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	OmpManager::Get()->objects->release(object_->getID());
	IPC_RETURN();
}

IPC_API(Object_AttachToVehicle, uintptr_t object, uintptr_t vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	if (vehicle)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
		object_->attachToVehicle(*vehicle_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ });
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(Object_AttachToObject, uintptr_t object, uintptr_t objAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ, bool syncRotation)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	if (objAttachedTo)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, objAttachedTo, objAttachedTo_);
		object_->attachToObject(*objAttachedTo_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ }, syncRotation);
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(Object_AttachToPlayer, uintptr_t object, uintptr_t player, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	if (player)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
		object_->attachToPlayer(*player_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ });
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(Object_SetPos, uintptr_t object, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Object_GetPos, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const Vector3& position = object_->getPosition();
	float x = position.x;
	float y = position.y;
	float z = position.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Object_SetRot, uintptr_t object, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->setRotation({ rotationX, rotationY, rotationZ });
	IPC_RETURN();
}

IPC_API(Object_GetRot, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const Vector3& rotation = object_->getRotation().ToEuler();
	float rotationX = rotation.x;
	float rotationY = rotation.y;
	float rotationZ = rotation.z;
	IPC_RETURN(float rotationX, float rotationY, float rotationZ);
}

IPC_API(Object_GetModel, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	int model = object_->getModel();
	IPC_RETURN(int model);
}

IPC_API(Object_SetNoCameraCollision, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->setCameraCollision(false);
	IPC_RETURN();
}

IPC_API(Object_IsValid, uintptr_t object)
{
	if (OmpManager::Get()->objects == nullptr)
		return RETURN_ERROR("Pool for IObject is unavailable.");

	IObject* object_ = reinterpret_cast<IObject*>(object);
	auto valid = object_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Object_Move, uintptr_t object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	ObjectMoveData data;
	data.targetPos = { x, y, z };
	data.targetRot = { rotationX, rotationY, rotationZ };
	data.speed = speed;

	object_->move(data);

	float estimatedTime = (glm::length(data.targetPos - object_->getPosition()) / speed) * 1000.0f;
	int time = static_cast<int>(estimatedTime);
	IPC_RETURN(int time);
}

IPC_API(Object_Stop, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->stop();
	IPC_RETURN();
}

IPC_API(Object_IsMoving, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	bool moving = object_->isMoving();
	IPC_RETURN(bool moving);
}

IPC_API(Object_BeginEditing, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	data->beginEditing(*object_);
	IPC_RETURN();
}

IPC_API(Object_BeginSelecting, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	data->beginSelecting();
	IPC_RETURN();
}

IPC_API(Object_EndEditing, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	data->endEditing();
	IPC_RETURN();
}

IPC_API(Object_SetMaterial, uintptr_t object, int materialIndex, int modelId, ConstStringRef textureLibrary, ConstStringRef textureName, uint32_t materialColour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->setMaterial(materialIndex, modelId, textureLibrary, textureName, Colour::FromARGB(materialColour));
	IPC_RETURN();
}

IPC_API(Object_SetMaterialText, uintptr_t object, ConstStringRef text, int materialIndex, int materialSize, ConstStringRef fontface, int fontsize, bool bold, uint32_t fontColour, uint32_t backgroundColour, int textalignment)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	object_->setMaterialText(materialIndex, text, ObjectMaterialSize(materialSize), fontface, fontsize, bold, Colour::FromARGB(fontColour), Colour::FromARGB(backgroundColour), ObjectMaterialTextAlign(textalignment));
	IPC_RETURN();
}

IPC_API(Object_SetDefaultCameraCollision, bool disable)
{
	IObjectsComponent* objects = OmpManager::Get()->objects;
	if (objects)
	{
		objects->setDefaultCameraCollision(!disable);
		IPC_RETURN();
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Object_GetDrawDistance, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	float distance = object_->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(Object_GetMoveSpeed, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	float speed = object_->getMovingData().speed;
	IPC_RETURN(float speed);
}

IPC_API(Object_GetMovingTargetPos, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectMoveData& data = object_->getMovingData();
	float targetX = data.targetPos.x;
	float targetY = data.targetPos.y;
	float targetZ = data.targetPos.z;
	IPC_RETURN(float targetX, float targetY, float targetZ);
}

IPC_API(Object_GetMovingTargetRot, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectMoveData& data = object_->getMovingData();
	float rotationX = data.targetRot.x;
	float rotationY = data.targetRot.y;
	float rotationZ = data.targetRot.z;
	IPC_RETURN(float rotationX, float rotationY, float rotationZ);
}

IPC_API(Object_GetAttachedData, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectAttachmentData data = object_->getAttachmentData();
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

	IPC_RETURN(int parentVehicle, int parentObject, int parentPlayer);
}

IPC_API(Object_GetAttachedOffset, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectAttachmentData data = object_->getAttachmentData();
	float offsetX = data.offset.x;
	float offsetY = data.offset.y;
	float offsetZ = data.offset.z;
	float rotationX = data.rotation.x;
	float rotationY = data.rotation.y;
	float rotationZ = data.rotation.z;
	IPC_RETURN(float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
}

IPC_API(Object_GetSyncRotation, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	float rotation = object_->getAttachmentData().syncRotation;
	IPC_RETURN(float rotation);
}

IPC_API(Object_IsMaterialSlotUsed, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		bool used = data->used;
		IPC_RETURN(bool used);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Object_GetMaterial, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		int modelid = data->model;
		ConstStringRef textureLibrary = data->textOrTXD.data();
		ConstStringRef textureName = data->fontOrTexture.data();
		int materialColour = data->materialColour.ARGB();
		IPC_RETURN(int modelid, ConstStringRef textureLibrary, ConstStringRef textureName, int materialColour);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Object_GetMaterialText, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		ConstStringRef text = data->textOrTXD.data();
		int materialSize = data->materialSize;
		ConstStringRef fontFace = data->fontOrTexture.data();
		int fontSize = data->fontSize;
		bool bold = data->bold;
		int fontColour = data->fontColour.ARGB();
		int backgroundColour = data->backgroundColour.ARGB();
		int textAlignment = data->alignment;
		IPC_RETURN(ConstStringRef text, int materialSize, ConstStringRef fontFace, int fontSize, bool bold, int fontColour, int backgroundColour, int textAlignment);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Object_IsObjectNoCameraCollision, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->objects, IObject, object, object_);
	bool collision = !object_->getCameraCollision();
	IPC_RETURN(bool collision);
}

IPC_API(Object_GetType, uintptr_t player, int objectid)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	if (data->get(objectid) != nullptr)
	{
		uint8_t type = 2; // Player object type
		IPC_RETURN(uint8_t type);
	}

	IObjectsComponent* component = OmpManager::Get()->objects;
	if (component)
	{
		if (component->get(objectid) != nullptr)
		{
			uint8_t type = 1; // Global object type
			IPC_RETURN(uint8_t type);
		}
	}

	return FUNCTION_FAIL_RETURN;
}

/*
	Per-Player Objects
*/

IPC_API(PlayerObject_Create, uintptr_t player, int modelid, float x, float y, float z, float rotationX, float rotationY, float rotationZ, float drawDistance)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	IPlayerObject* object = data->create(modelid, { x, y, z }, { rotationX, rotationY, rotationZ }, drawDistance);
	if (object)
	{
		auto id = object->getID();
		auto ptr = reinterpret_cast<uintptr_t>(object);
		IPC_RETURN(int id, uintptr_t ptr);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerObject_Destroy, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);
	data->release(object_->getID());
	IPC_RETURN();
}

IPC_API(PlayerObject_AttachToVehicle, uintptr_t player, uintptr_t object, uintptr_t vehicle, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	if (vehicle)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
		object_->attachToVehicle(*vehicle_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ });
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(PlayerObject_AttachToPlayer, uintptr_t player, uintptr_t object, uintptr_t playerAttachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	if (playerAttachedTo)
	{
		GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, playerAttachedTo, playerAttachedTo_);
		object_->attachToPlayer(*playerAttachedTo_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ });
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(PlayerObject_AttachToObject, uintptr_t player, uintptr_t object, uintptr_t attachedTo, float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	if (attachedTo)
	{
		GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, attachedTo, attachedTo_);
		object_->attachToObject(*attachedTo_, { offsetX, offsetY, offsetZ }, { rotationX, rotationY, rotationZ });
	}
	else
	{
		object_->resetAttachment();
	}
	IPC_RETURN();
}

IPC_API(PlayerObject_SetPos, uintptr_t player, uintptr_t object, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(PlayerObject_GetPos, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const Vector3& position = object_->getPosition();
	float x = position.x;
	float y = position.y;
	float z = position.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(PlayerObject_SetRot, uintptr_t player, uintptr_t object, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->setRotation({ rotationX, rotationY, rotationZ });
	IPC_RETURN();
}

IPC_API(PlayerObject_GetRot, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const Vector3& rotation = object_->getRotation().ToEuler();
	float rotationX = rotation.x;
	float rotationY = rotation.y;
	float rotationZ = rotation.z;
	IPC_RETURN(float rotationX, float rotationY, float rotationZ);
}

IPC_API(PlayerObject_GetModel, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	if (!object)
	{
		return FUNCTION_FAIL_RETURN;
	}
	int model = object_->getModel();
	IPC_RETURN(int model);
}

IPC_API(PlayerObject_SetNoCameraCollision, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->setCameraCollision(false);
	IPC_RETURN();
}

IPC_API(PlayerObject_IsValid, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto pool_instance = GetPlayerData<IPlayerObjectData>(player_);
	if (pool_instance == nullptr)
		return RETURN_ERROR("Pool for IPlayerObject is unavailable.");

	IPlayerObject* object_ = reinterpret_cast<IPlayerObject*>(object);
	auto valid = object_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(PlayerObject_Move, uintptr_t player, uintptr_t object, float x, float y, float z, float speed, float rotationX, float rotationY, float rotationZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	ObjectMoveData data;
	data.targetPos = { x, y, z };
	data.targetRot = { rotationX, rotationY, rotationZ };
	data.speed = speed;

	object_->move(data);

	float estimatedTime = (glm::length(data.targetPos - object_->getPosition()) / speed) * 1000.0f;
	int time = static_cast<int>(estimatedTime);
	IPC_RETURN(int time);
}

IPC_API(PlayerObject_Stop, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->stop();
	IPC_RETURN();
}

IPC_API(PlayerObject_IsMoving, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	bool moving = object_->isMoving();
	IPC_RETURN(bool moving);
}

IPC_API(PlayerObject_BeginEditing, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerObjectData* data = queryExtension<IPlayerObjectData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}

	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);
	data->beginEditing(*object_);
	IPC_RETURN();
}

IPC_API(PlayerObject_SetMaterial, uintptr_t player, uintptr_t object, int materialIndex, int modelId, ConstStringRef textureLibrary, ConstStringRef textureName, uint32_t materialColour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->setMaterial(materialIndex, modelId, textureLibrary, textureName, Colour::FromARGB(materialColour));
	IPC_RETURN();
}

IPC_API(PlayerObject_SetMaterialText, uintptr_t player, uintptr_t object, ConstStringRef text, int materialIndex, int materialSize, ConstStringRef fontface, int fontsize, bool bold, uint32_t fontColour, uint32_t backgroundColour, int textalignment)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	object_->setMaterialText(materialIndex, text, ObjectMaterialSize(materialSize), fontface, fontsize, bold, Colour::FromARGB(fontColour), Colour::FromARGB(backgroundColour), ObjectMaterialTextAlign(textalignment));
	IPC_RETURN();
}

IPC_API(PlayerObject_GetDrawDistance, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	float distance = object_->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(PlayerObject_GetMoveSpeed, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	float speed = object_->getMovingData().speed;
	IPC_RETURN(float speed);
}

IPC_API(PlayerObject_GetMovingTargetPos, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectMoveData& data = object_->getMovingData();
	float targetX = data.targetPos.x;
	float targetY = data.targetPos.y;
	float targetZ = data.targetPos.z;
	IPC_RETURN(float targetX, float targetY, float targetZ);
}

IPC_API(PlayerObject_GetMovingTargetRot, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectMoveData& data = object_->getMovingData();
	float rotationX = data.targetRot.x;
	float rotationY = data.targetRot.y;
	float rotationZ = data.targetRot.z;
	IPC_RETURN(float rotationX, float rotationY, float rotationZ);
}

IPC_API(PlayerObject_GetAttachedData, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectAttachmentData data = object_->getAttachmentData();
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

	IPC_RETURN(int parentVehicle, int parentObject, int parentPlayer);
}

IPC_API(PlayerObject_GetAttachedOffset, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectAttachmentData data = object_->getAttachmentData();
	float offsetX = data.offset.x;
	float offsetY = data.offset.y;
	float offsetZ = data.offset.z;
	float rotationX = data.rotation.x;
	float rotationY = data.rotation.y;
	float rotationZ = data.rotation.z;
	IPC_RETURN(float offsetX, float offsetY, float offsetZ, float rotationX, float rotationY, float rotationZ);
}

IPC_API(PlayerObject_GetSyncRotation, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	float rotation = object_->getAttachmentData().syncRotation;
	IPC_RETURN(float rotation);
}

IPC_API(PlayerObject_IsMaterialSlotUsed, uintptr_t player, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		bool used = data->used;
		IPC_RETURN(bool used);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerObject_GetMaterial, uintptr_t player, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		int modelid = data->model;
		ConstStringRef textureLibrary = data->textOrTXD.data();
		ConstStringRef textureName = data->fontOrTexture.data();
		int materialColour = data->materialColour.ARGB();
		IPC_RETURN(int modelid, ConstStringRef textureLibrary, ConstStringRef textureName, int materialColour);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerObject_GetMaterialText, uintptr_t player, uintptr_t object, int materialIndex)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	const ObjectMaterialData* data = nullptr;
	bool result = object_->getMaterialData(materialIndex, data);
	if (result)
	{
		ConstStringRef text = data->textOrTXD.data();
		int materialSize = data->materialSize;
		ConstStringRef fontFace = data->fontOrTexture.data();
		int fontSize = data->fontSize;
		bool bold = data->bold;
		int fontColour = data->fontColour.ARGB();
		int backgroundColour = data->backgroundColour.ARGB();
		int textAlignment = data->alignment;
		IPC_RETURN(ConstStringRef text, int materialSize, ConstStringRef fontFace, int fontSize, bool bold, int fontColour, int backgroundColour, int textAlignment);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerObject_IsNoCameraCollision, uintptr_t player, uintptr_t object)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerObjectData, IPlayerObject, object, object_);

	bool collision = !object_->getCameraCollision();
	IPC_RETURN(bool collision);
}

IPC_API(Player_GetSurfingPlayerObject, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);

	const PlayerSurfingData& data = player_->getSurfingData();
	if (data.type == PlayerSurfingData::Type::PlayerObject)
	{
		auto id = data.ID;
		auto ptr = reinterpret_cast<uintptr_t>(&data.ID); //object id to pointer
		IPC_RETURN(int id, uintptr_t ptr);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Player_GetCameraTargetPlayerObject, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IObject* object = player_->getCameraTargetObject();
	if (object)
	{
		auto id = object->getID();
		auto ptr = reinterpret_cast<uintptr_t>(object);
		IPC_RETURN(int id, uintptr_t ptr);
	}
	return FUNCTION_FAIL_RETURN;
}
