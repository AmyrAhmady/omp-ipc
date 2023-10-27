#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(TextLabel3D_Create, const nlohmann::json& params)
{
	ITextLabelsComponent* component = OmpManager::Get()->textlabels;
	if (component)
	{
		ITextLabel* textlabel = component->create(
			params["text"], 
			Colour::FromRGBA(params["colour"]), 
			{ params["x"], params["y"], params["z"] }, 
			params["drawDistance"], 
			params["virtualWorld"], 
			params["los"]);

		if (textlabel)
		{
			nlohmann::json ret;
			ret["ret_value"]["id"] = textlabel->getID();
			ret["ret_value"]["textlabel"] = reinterpret_cast<uintptr_t>(textlabel);
			return ret;
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(TextLabel3D_Delete, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	OmpManager::Get()->textlabels->release(textlabel->getID());
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_AttachToPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	textlabel->attachToPlayer(
		player, 
		{ params["offsetX"], params["offsetY"], params["offsetZ"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_AttachToVehicle, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["parent"], vehicle);
	textlabel->attachToVehicle(
		vehicle, 
		{ params["offsetX"], params["offsetY"], params["offsetZ"] });
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_UpdateText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	textlabel->setColourAndText(Colour::FromRGBA(params["colour"]), params["text"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->textlabels == nullptr)
		return "{\"ret_value\":{\"error\":\"Pool for ITextLabel is unavailable.\"}}"_json;

	ITextLabel* textlabel = reinterpret_cast<ITextLabel*>(uintptr_t(params["textlabel"]));
	return RETURN_VALUE(textlabel != nullptr);
}

IPC_API(TextLabel3D_IsStreamedIn, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	return textlabel->isStreamedInForPlayer(player);
}

IPC_API(TextLabel3D_GetText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getText());
}

IPC_API(TextLabel3D_GetColour, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getColour().RGBA());
}

IPC_API(TextLabel3D_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	nlohmann::json ret;
	const Vector3& pos = textlabel->getPosition();
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(TextLabel3D_SetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	textlabel->setDrawDistance(params["distance"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_GetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getDrawDistance());
}

IPC_API(TextLabel3D_GetLOS, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getTestLOS());
}

IPC_API(TextLabel3D_SetLOS, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	textlabel->setTestLOS(params["status"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_GetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getVirtualWorld());
}

IPC_API(TextLabel3D_SetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	textlabel->setVirtualWorld(params["world"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(TextLabel3D_GetAttachedData, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, params["textlabel"], textlabel);
	const TextLabelAttachmentData& data = textlabel->getAttachmentData();

	nlohmann::json ret;
	ret["parentPlayerid"] = data.playerID;
	ret["parentVehicleid"] = data.vehicleID;
	return RETURN_VALUE(ret);
}

/*
	Per-Player 3DTextLabels
*/

IPC_API(PlayerTextLabel3D_Create, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerTextLabelData* labelData = queryExtension<IPlayerTextLabelData>(player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["parentPlayerid"], attachedPlayer);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, params["parentVehicleid"], attachedVehicle);

	if (labelData)
	{
		IPlayerTextLabel* textlabel = nullptr;

		if (attachedPlayer)
		{
			textlabel = labelData->create(
				params["text"], 
				Colour::FromRGBA(params["colour"]), 
				{ params["x"], params["y"], params["z"] }, 
				params["drawDistance"], 
				params["los"], 
				*attachedPlayer);
		}
		else if (attachedVehicle)
		{
			textlabel = labelData->create(
				params["text"], 
				Colour::FromRGBA(params["colour"]), 
				{ params["x"], params["y"], params["z"] }, 
				params["drawDistance"], 
				params["los"], 
				*attachedVehicle);
		}
		else
		{
			textlabel = labelData->create(
				params["text"], 
				Colour::FromRGBA(params["colour"]), 
				{ params["x"], params["y"], params["z"] }, 
				params["drawDistance"], 
				params["los"]);
		}

		if (textlabel)
		{
			nlohmann::json ret;
			ret["ret_value"]["id"] = textlabel->getID();
			ret["ret_value"]["textlabel"] = reinterpret_cast<uintptr_t>(textlabel);
			return ret;
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(PlayerTextLabel3D_Delete, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	auto data = queryExtension<IPlayerTextLabelData>(player);
	if (!data)
	{
		return RETURN_VALUE(false);
	}
	data->release(textlabel->getID());
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerTextLabel3D_UpdateText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	textlabel->setColourAndText(Colour::FromRGBA(params["colour"]), params["text"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerTextLabel3D_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->playertextlabels == nullptr)
		return "{\"ret_value\":{\"error\":\"Pool for IPlayerTextLabel is unavailable.\"}}"_json;

	IPlayerTextLabel* textlabel = reinterpret_cast<IPlayerTextLabel*>(uintptr_t(params["textlabel"]));
	return RETURN_VALUE(textlabel != nullptr);
}

IPC_API(PlayerTextLabel3D_GetText, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getText());
}

IPC_API(PlayerTextLabel3D_GetColour, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getColour().RGBA());
}

IPC_API(PlayerTextLabel3D_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	nlohmann::json ret;
	const Vector3& pos = textlabel->getPosition();
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	ret["z"] = pos.z;
	return RETURN_VALUE(ret);
}

IPC_API(PlayerTextLabel3D_SetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	textlabel->setDrawDistance(params["distance"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerTextLabel3D_GetDrawDistance, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getDrawDistance());
}

IPC_API(PlayerTextLabel3D_GetLOS, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	return RETURN_VALUE(textlabel->getTestLOS());
}

IPC_API(PlayerTextLabel3D_SetLOS, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	textlabel->setTestLOS(params["status"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(PlayerTextLabel3D_GetVirtualWorld, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	// No virtual world support, returning player virtual world.
	return RETURN_VALUE(player->getVirtualWorld());
}

//  IPC_API(PlayerTextLabel3D_SetVirtualWorld, const nlohmann::json& params)
//  {
//      Why is there no virtual world support?
//  }

IPC_API(PlayerTextLabel3D_GetAttachedData, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, params["textlabel"], textlabel);
	const TextLabelAttachmentData& data = textlabel->getAttachmentData();

	nlohmann::json ret;
	ret["parentPlayerid"] = data.playerID;
	ret["parentVehicleid"] = data.vehicleID;
	return RETURN_VALUE(ret);
}