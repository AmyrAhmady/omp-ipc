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

IPC_API(TextLabel3D_Delete, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	OmpManager::Get()->textlabels->release(textlabel_->getID());
	IPC_RETURN();
}

IPC_API(TextLabel3D_AttachToPlayer, uintptr_t textlabel, uintptr_t player, float offsetX, float offsetY, float offsetZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	textlabel_->attachToPlayer(*player_, { offsetX, offsetY, offsetZ });
	IPC_RETURN();
}

IPC_API(TextLabel3D_AttachToVehicle, uintptr_t textlabel, uintptr_t vehicle, float offsetX, float offsetY, float offsetZ)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	textlabel_->attachToVehicle(*vehicle_, { offsetX, offsetY, offsetZ });
	IPC_RETURN();
}

IPC_API(TextLabel3D_UpdateText, uintptr_t textlabel, uint32_t colour, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setColourAndText(Colour::FromRGBA(colour), text);
	IPC_RETURN();
}

IPC_API(TextLabel3D_IsValid, uintptr_t textlabel)
{
	if (OmpManager::Get()->textlabels == nullptr)
		return RETURN_ERROR("Pool for ITextLabel is unavailable.");

	ITextLabel* textlabel_ = reinterpret_cast<ITextLabel*>(textlabel);
	auto valid = textlabel_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(TextLabel3D_IsStreamedIn, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	auto streamed = textlabel_->isStreamedInForPlayer(*player_);
	IPC_RETURN(bool streamed);
}

IPC_API(TextLabel3D_GetText, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	ConstStringRef output = textlabel_->getText().data();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(TextLabel3D_GetColor, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	auto colour = textlabel_->getColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextLabel3D_GetPos, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	const Vector3& pos = textlabel_->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(TextLabel3D_SetDrawDistance, uintptr_t textlabel, float distance)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setDrawDistance(distance);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetDrawDistance, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	auto distance = textlabel_->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(TextLabel3D_GetLOS, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	auto los = textlabel_->getTestLOS();
	IPC_RETURN(bool los);
}

IPC_API(TextLabel3D_SetLOS, uintptr_t textlabel, bool status)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setTestLOS(status);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetVirtualWorld, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	auto virtualWorld = textlabel_->getVirtualWorld();
	IPC_RETURN(int virtualWorld);
}

IPC_API(TextLabel3D_SetVirtualWorld, uintptr_t textlabel, int world)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	textlabel_->setVirtualWorld(world);
	IPC_RETURN();
}

IPC_API(TextLabel3D_GetAttachedData, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textlabels, ITextLabel, textlabel, textlabel_);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

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
			GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, attachedPlayer, attachedPlayer_);
			textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, los, *attachedPlayer_);
		}
		else if (attachedVehicle)
		{
			GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, attachedVehicle, attachedVehicle_);
			textlabel = labelData->create(text, Colour::FromRGBA(colour), { x, y, z }, drawDistance, los, *attachedVehicle_);
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

IPC_API(PlayerTextLabel3D_Delete, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto data = queryExtension<IPlayerTextLabelData>(player_);
	if (!data)
	{
		return FUNCTION_FAIL_RETURN;
	}
	data->release(textlabel_->getID());
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_UpdateText, uintptr_t player, uintptr_t textlabel, uint32_t colour, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setColourAndText(Colour::FromRGBA(colour), text);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_IsValid, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	auto pool_instance = GetPlayerData<IPlayerTextLabelData>(player_);
	if (pool_instance == nullptr)
		return RETURN_ERROR("Pool for IPlayerTextLabel is unavailable.");

	IPlayerTextLabel* textlabel_ = reinterpret_cast<IPlayerTextLabel*>(textlabel);
	auto valid = textlabel_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(PlayerTextLabel3D_GetText, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	ConstStringRef output = textlabel_->getText().data();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(PlayerTextLabel3D_GetColor, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto colour = textlabel_->getColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(PlayerTextLabel3D_GetPos, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	const Vector3& pos = textlabel_->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	auto z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(PlayerTextLabel3D_SetDrawDistance, uintptr_t player, uintptr_t textlabel, float distance)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setDrawDistance(distance);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_GetDrawDistance, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto distance = textlabel_->getDrawDistance();
	IPC_RETURN(float distance);
}

IPC_API(PlayerTextLabel3D_GetLOS, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	auto los = textlabel_->getTestLOS();
	IPC_RETURN(bool los);
}

IPC_API(PlayerTextLabel3D_SetLOS, uintptr_t player, uintptr_t textlabel, bool status)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	textlabel_->setTestLOS(status);
	IPC_RETURN();
}

IPC_API(PlayerTextLabel3D_GetVirtualWorld, uintptr_t player, uintptr_t textlabel)
{
	// No virtual world support, returning player virtual world.
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	return player_->getVirtualWorld();
}

IPC_API(PlayerTextLabel3D_GetAttachedData, uintptr_t player, uintptr_t textlabel)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextLabelData, IPlayerTextLabel, textlabel, textlabel_);
	const TextLabelAttachmentData& data = textlabel_->getAttachmentData();

	auto attached_player = data.playerID;
	auto attached_vehicle = data.vehicleID;

	IPC_RETURN(int attached_player, int attached_vehicle);
}
