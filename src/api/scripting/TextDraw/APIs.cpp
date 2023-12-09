#include "../Manager.hpp"

IPC_API(TextDraw_Create, float x, float y, ConstStringRef text)
{
	ITextDrawsComponent* component = OmpManager::Get()->textdraws;
	if (component)
	{
		ITextDraw* textdraw = component->create({ x, y }, text);
		if (textdraw)
		{
			auto id = textdraw->getID();
			auto ptr = reinterpret_cast<uintptr_t>(textdraw);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(TextDraw_Destroy, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	OmpManager::Get()->textdraws->release(textdraw_->getID());
	IPC_RETURN();
}

IPC_API(TextDraw_IsValid, uintptr_t textdraw)
{
	if (OmpManager::Get()->textdraws == nullptr)
		return RETURN_ERROR("Pool for ITextDraw is unavailable.");

	ITextDraw* textdraw_ = reinterpret_cast<ITextDraw*>(textdraw);
	auto valid = textdraw_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(TextDraw_IsVisibleForPlayer, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	// TODO: Deprecate this native.  Mixing `visible` and `show` is bad.  In fact, just avoid the
	// term `visible` entirely - it is too ambiguous when things might be available to a player but
	// out of their current line of sight.  Does `visible` mean "can be seen right now" or "can in
	// theory be seen some time"?  In this respect `shown` and `streamed` are less ambiguous.
	auto shown = textdraw_->isShownForPlayer(*player_);
	IPC_RETURN(bool shown);
}

IPC_API(TextDraw_SetLetterSize, uintptr_t textdraw, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setLetterSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(TextDraw_SetTextSize, uintptr_t textdraw, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setTextSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(TextDraw_SetAlignment, uintptr_t textdraw, int alignment)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setAlignment(TextDrawAlignmentTypes(alignment));
	IPC_RETURN();
}

IPC_API(TextDraw_SetColour, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetUseBox, uintptr_t textdraw, bool use)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->useBox(use);
	IPC_RETURN();
}

IPC_API(TextDraw_SetBoxColour, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setBoxColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetShadow, uintptr_t textdraw, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setShadow(size);
	IPC_RETURN();
}

IPC_API(TextDraw_SetOutline, uintptr_t textdraw, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setOutline(size);
	IPC_RETURN();
}

IPC_API(TextDraw_SetBackgroundColour, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setBackgroundColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetFont, uintptr_t textdraw, int font)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setStyle(TextDrawStyle(font));
	IPC_RETURN();
}

IPC_API(TextDraw_SetSetProportional, uintptr_t textdraw, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setProportional(set);
	IPC_RETURN();
}

IPC_API(TextDraw_SetSelectable, uintptr_t textdraw, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setSelectable(set);
	IPC_RETURN();
}

IPC_API(TextDraw_ShowForPlayer, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->showForPlayer(*player_);
	IPC_RETURN();
}

IPC_API(TextDraw_HideForPlayer, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->hideForPlayer(*player_);
	IPC_RETURN();
}

IPC_API(TextDraw_ShowForAll, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	IPlayerPool* pool = OmpManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw_->showForPlayer(*player);
	}
	IPC_RETURN();
}

IPC_API(TextDraw_HideForAll, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	IPlayerPool* pool = OmpManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw_->hideForPlayer(*player);
	}
	IPC_RETURN();
}

IPC_API(TextDraw_SetString, uintptr_t textdraw, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setText(text);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewModel, uintptr_t textdraw, int model)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setPreviewModel(model);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewRotation, uintptr_t textdraw, float rotationX, float rotationY, float rotationZ, float zoom)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setPreviewRotation({ rotationX, rotationY, rotationZ });
	textdraw_->setPreviewZoom(zoom);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewVehicleColour, uintptr_t textdraw, int colour1, int colour2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setPreviewVehicleColour(colour1, colour2);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPos, uintptr_t textdraw, float x, float y)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	textdraw_->setPosition({ x, y });
	IPC_RETURN();
}

IPC_API(TextDraw_GetString, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	ConstStringRef text = textdraw_->getText().data();
	IPC_RETURN(ConstStringRef text);
}

IPC_API(TextDraw_GetLetterSize, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	const Vector2& size = textdraw_->getLetterSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(TextDraw_GetTextSize, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	const Vector2& size = textdraw_->getTextSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(TextDraw_GetPos, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	const Vector2& pos = textdraw_->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	IPC_RETURN(float x, float y);
}

IPC_API(TextDraw_GetColour, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getLetterColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetBoxColour, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getBoxColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetBackgroundColour, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getBackgroundColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetShadow, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto size = textdraw_->getShadow();
	IPC_RETURN(int size);
}

IPC_API(TextDraw_GetOutline, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto size = textdraw_->getOutline();
	IPC_RETURN(int size);
}

IPC_API(TextDraw_GetFont, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto font = static_cast<uint8_t>(textdraw_->getStyle());
	IPC_RETURN(int font);
}

IPC_API(TextDraw_IsBox, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto set = textdraw_->hasBox();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_IsProportional, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto set = textdraw_->isProportional();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_IsSelectable, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto set = textdraw_->isSelectable();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_GetAlignment, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	auto alignment = static_cast<uint8_t>(textdraw_->getAlignment());
	IPC_RETURN(int alignment);
}

IPC_API(TextDraw_GetPreviewModel, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	int model = textdraw_->getPreviewModel();
	IPC_RETURN(int model);
}

IPC_API(TextDraw_GetPreviewRotation, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	const Vector3& rotation = textdraw_->getPreviewRotation();
	auto x = rotation.x;
	auto y = rotation.y;
	auto z = rotation.z;
	auto zoom = textdraw_->getPreviewZoom();
	IPC_RETURN(float x, float y, float z, float zoom);
}

IPC_API(TextDraw_GetPreviewVehicleColour, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	Pair<int, int> colours = textdraw_->getPreviewVehicleColour();
	auto colour1 = colours.first;
	auto colour2 = colours.second;
	IPC_RETURN(int colour1, int colour2);
}

IPC_API(TextDraw_SetStringForPlayer, uintptr_t textdraw, uintptr_t player, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, textdraw, textdraw_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	textdraw_->setTextForPlayer(*player_, text);
	IPC_RETURN();
}

/*
	Per-Player Textdraws
*/

IPC_API(PlayerTextDraw_Create, uintptr_t player, float x, float y, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerTextDrawData* playerTextDraws = queryExtension<IPlayerTextDrawData>(player_);
	if (playerTextDraws)
	{
		IPlayerTextDraw* textdraw = playerTextDraws->create({ x, y }, text);
		if (textdraw)
		{
			auto id = textdraw->getID();
			auto ptr = reinterpret_cast<uintptr_t>(textdraw);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerTextDraw_Destroy, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerTextDrawData* playerTextDraws = queryExtension<IPlayerTextDrawData>(player_);
	if (playerTextDraws)
	{
		GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
		playerTextDraws->release(textdraw_->getID());
		IPC_RETURN();
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(PlayerTextDraw_IsValid, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerTextDrawData* playerTextDraws = queryExtension<IPlayerTextDrawData>(player_);
	bool valid = false;
	if (playerTextDraws)
	{
		IPlayerTextDraw* textdraw_ = reinterpret_cast<IPlayerTextDraw*>(textdraw);
		if (textdraw_ != nullptr) {
			valid = true;
		}
	}
	IPC_RETURN(bool valid);
}

IPC_API(PlayerTextDraw_IsVisible, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	bool shown = textdraw_->isShown();
	IPC_RETURN(bool shown);
}

IPC_API(PlayerTextDraw_SetLetterSize, uintptr_t player, uintptr_t textdraw, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setLetterSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetTextSize, uintptr_t player, uintptr_t textdraw, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setTextSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetAlignment, uintptr_t player, uintptr_t textdraw, int alignment)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setAlignment(TextDrawAlignmentTypes(alignment));
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetColour, uintptr_t player, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetUseBox, uintptr_t player, uintptr_t textdraw, bool use)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->useBox(use);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetBoxColour, uintptr_t player, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setBoxColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetShadow, uintptr_t player, uintptr_t textdraw, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setShadow(size);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetOutline, uintptr_t player, uintptr_t textdraw, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setOutline(size);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetBackgroundColour, uintptr_t player, uintptr_t textdraw, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setBackgroundColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetFont, uintptr_t player, uintptr_t textdraw, int font)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setStyle(TextDrawStyle(font));
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetProportional, uintptr_t player, uintptr_t textdraw, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setProportional(set);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetSelectable, uintptr_t player, uintptr_t textdraw, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setSelectable(set);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_Show, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->show();
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_Hide, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->hide();
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetString, uintptr_t player, uintptr_t textdraw, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setText(text);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetPreviewModel, uintptr_t player, uintptr_t textdraw, int model)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setPreviewModel(model);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetPreviewRotation, uintptr_t player, uintptr_t textdraw, float rotationX, float rotationY, float rotationZ, float zoom)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setPreviewRotation({ rotationX, rotationY, rotationZ });
	textdraw_->setPreviewZoom(zoom);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetPreviewVehicleColour, uintptr_t player, uintptr_t textdraw, int colour1, int colour2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setPreviewVehicleColour(colour1, colour2);
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_SetPos, uintptr_t player, uintptr_t textdraw, float x, float y)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	textdraw_->setPosition({ x, y });
	IPC_RETURN();
}

IPC_API(PlayerTextDraw_GetString, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	ConstStringRef text = textdraw_->getText().data();
	IPC_RETURN(ConstStringRef text);
}

IPC_API(PlayerTextDraw_GetLetterSize, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	const Vector2& size = textdraw_->getLetterSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(PlayerTextDraw_GetTextSize, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	const Vector2& size = textdraw_->getTextSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(PlayerTextDraw_GetPos, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	const Vector2& pos = textdraw_->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	IPC_RETURN(float x, float y);
}

IPC_API(PlayerTextDraw_GetColour, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getLetterColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(PlayerTextDraw_GetBoxColour, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getBoxColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(PlayerTextDraw_GetBackgroundColour, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto colour = textdraw_->getBackgroundColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(PlayerTextDraw_GetShadow, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	int size = textdraw_->getShadow();
	IPC_RETURN(int size);
}

IPC_API(PlayerTextDraw_GetOutline, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	int size = textdraw_->getOutline();
	IPC_RETURN(int size);
}

IPC_API(PlayerTextDraw_GetFont, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto font = static_cast<uint8_t>(textdraw_->getStyle());
	IPC_RETURN(int font);
}

IPC_API(PlayerTextDraw_IsBox, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto set = textdraw_->hasBox();
	IPC_RETURN(bool set);
}

IPC_API(PlayerTextDraw_IsProportional, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto set = textdraw_->isProportional();
	IPC_RETURN(bool set);
}

IPC_API(PlayerTextDraw_IsSelectable, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto set = textdraw_->isSelectable();
	IPC_RETURN(bool set);
}

IPC_API(PlayerTextDraw_GetAlignment, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	auto alignment = static_cast<uint8_t>(textdraw_->getAlignment());
	IPC_RETURN(int alignment);
}

IPC_API(PlayerTextDraw_GetPreviewModel, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	int model = textdraw_->getPreviewModel();
	IPC_RETURN(int model);
}

IPC_API(PlayerTextDraw_GetPreviewRotation, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	const Vector3& rotation = textdraw_->getPreviewRotation();
	auto x = rotation.x;
	auto y = rotation.y;
	auto z = rotation.z;
	auto zoom = textdraw_->getPreviewZoom();
	IPC_RETURN(float x, float y, float z, float zoom);
}

IPC_API(PlayerTextDraw_GetPreviewVehicleColour, uintptr_t player, uintptr_t textdraw)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_PLAYER_POOL_ENTITY_CHECKED(player_, IPlayerTextDrawData, IPlayerTextDraw, textdraw, textdraw_);
	Pair<int, int> colours = textdraw_->getPreviewVehicleColour();
	int colour1 = colours.first;
	int colour2 = colours.second;
	IPC_RETURN(int colour1, int colour2);
}
