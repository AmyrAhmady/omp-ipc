#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(TextLabel3D_Create, ConstStringRef text, uint32_t colour, float x, float y, float z, float drawDistance, int virtualWorld, bool los)
{
	ITextLabelsComponent* component = OmpManager::Get()->textlabels;
	if (component)
	{
		ITextLabel* textlabel = component->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, virtualWorld, los);
		if (textlabel)
		{
			auto id = textlabel->getID();
			auto ptr = reinterpret_cast<uintptr_t>(textlabel);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(TextLabel3D_Delete, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	OmpManager::Get()->textlabels->release(textlabel->getID());
	IPC_RETURN();
}

IPC_API(TextLabel3D_AttachToPlayer, uintptr_t ptr, uintptr_t player, float offsetX, float offsetY, float offsetZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	textlabel->attachToPlayer(player_, { offsetX, offsetY, offsetZ });
	IPC_RETURN();
}

IPC_API(TextLabel3D_AttachToVehicle, uintptr_t ptr, uintptr_t vehicle, float offsetX, float offsetY, float offsetZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	textlabel->attachToVehicle(vehicle_, { offsetX, offsetY, offsetZ });
	IPC_RETURN();
}

IPC_API(TextLabel3D_UpdateText, uintptr_t ptr, uint32_t colour, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	textlabel->setColourAndText(Colour::FromRGBA(colour), text);
	IPC_RETURN();
}

IPC_API(TextLabel3D_IsValid, uintptr_t ptr)
{
	if (OmpManager::Get()->textlabels == nullptr)
		return RETURN_ERROR("Pool for ITextLabel is unavailable.");

	ITextLabel* textlabel = reinterpret_cast<ITextLabel*>(ptr);
	auto valid = textlabel != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(TextLabel3D_IsStreamedIn, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	auto streamed = textlabel->isStreamedInForPlayer(player_);
	IPC_RETURN(bool streamed);
}

IPC_API(TextLabel3D_GetText, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	ConstStringRef output = textlabel->getText();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(TextLabel3D_GetColor, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	auto colour = textlabel->getColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextLabel3D_GetPos, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	const Vector3& pos = textlabel->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(TextLabel3D_SetDrawDistance, uintptr_t ptr, float distance)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	textlabel->setDrawDistance(distance);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetDrawDistance, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	auto distance = textlabel->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(TextLabel3D_GetLOS, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	auto los = textlabel->getTestLOS();
	IPC_RETURN(bool los);
}

IPC_API(TextLabel3D_SetLOS, uintptr_t ptr, bool status)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	textlabel->setTestLOS(status);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetVirtualWorld, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	auto virtualWorld = textlabel->getVirtualWorld();
	IPC_RETURN(int virtualWorld);
}

IPC_API(TextLabel3D_SetVirtualWorld, uintptr_t ptr, int world)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	textlabel->setVirtualWorld(world);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetAttachedData, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, ptr, textlabel);
	const TextLabelAttachmentData& data = textlabel->getAttachmentData();

	auto attached_player = data.playerID;
	auto attached_vehicle = data.vehicleID;

	IPC_RETURN(int attached_player, int attached_vehicle);
}

/*
	Per-Player TextLabel
*/

IPC_API(PlayerTextLabel3D_Create, uintptr_t player, ConstStringRef text, uint32_t colour, float x, float y, float z, float drawDistance, uintptr_t attachedPlayer, uintptr_t attachedVehicle, bool los)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerTextLabelData* labelData = queryExtension<IPlayerTextLabelData>(player_);
	if (labelData)
	{
		IPlayerTextLabel* textlabel = nullptr;

		if (attachedPlayer)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, los, *attachedPlayer);
		}
		else if (attachedVehicle)
		{
			textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, los, *attachedVehicle);
		}
		else
		{
			textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, los);
		}

		if (textlabel)
		{
			auto id = textlabel->getID();
			auto ptr = reinterpret_cast<uintptr_t>(textlabel);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerTextLabel3D_Delete, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	auto data = queryExtension<IPlayerTextLabelData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}
	data->release(textlabel->getID());
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_UpdateText, uintptr_t player, uintptr_t ptr, uint32_t colour, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	textlabel->setColourAndText(Colour::FromRGBA(colour), text);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_IsValid, uintptr_t player, uintptr_t ptr)
{
	if (OmpManager::Get()->playertextlabels == nullptr)
		return RETURN_ERROR("Pool for IPlayerTextLabel is unavailable.");

	IPlayerTextLabel* textlabel = reinterpret_cast<IPlayerTextLabel*>(ptr);
	auto valid = textlabel != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(PlayerTextLabel3D_GetText, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	ConstStringRef output = textlabel->getText();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(PlayerTextLabel3D_GetColor, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	auto colour = textlabel->getColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(PlayerTextLabel3D_GetPos, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	const Vector3& pos = textlabel->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(PlayerTextLabel3D_SetDrawDistance, uintptr_t player, uintptr_t ptr, float distance)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	textlabel->setDrawDistance(distance);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_GetDrawDistance, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	auto distance = textlabel->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(PlayerTextLabel3D_GetLOS, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	auto los = textlabel->getTestLOS();
	IPC_RETURN(bool los);
}

IPC_API(PlayerTextLabel3D_SetLOS, uintptr_t player, uintptr_t ptr, bool status)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	textlabel->setTestLOS(status);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_GetVirtualWorld, uintptr_t player, uintptr_t ptr)
{
	// No virtual world support, returning player virtual world.
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getVirtualWorld();
}

IPC_API(PlayerTextLabel3D_GetAttachedData, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->playertextlabels, IPlayerTextLabel, ptr, textlabel);
	const TextLabelAttachmentData& data = textlabel->getAttachmentData();

	auto attached_player = data.playerID;
	auto attached_vehicle = data.vehicleID;

	IPC_RETURN(int attached_player, int attached_vehicle);
}
