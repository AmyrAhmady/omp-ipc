#include "../../../message/Handler.hpp"
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

IPC_API(TextDraw_Destroy, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	OmpManager::Get()->textdraws->release(textdraw->getID());
	IPC_RETURN();
}

IPC_API(TextDraw_IsValid, uintptr_t ptr)
{
	if (OmpManager::Get()->textdraws == nullptr)
		return RETURN_ERROR("Pool for ITextDraw is unavailable.");

	ITextDraw* textdraw = reinterpret_cast<ITextDraw*>(ptr);
	auto valid = textdraw != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(TextDraw_IsVisibleForPlayer, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	// TODO: Deprecate this native.  Mixing `visible` and `show` is bad.  In fact, just avoid the
	// term `visible` entirely - it is too ambiguous when things might be available to a player but
	// out of their current line of sight.  Does `visible` mean "can be seen right now" or "can in
	// theory be seen some time"?  In this respect `shown` and `streamed` are less ambiguous.
	auto shown = textdraw->isShownForPlayer(player_);
	IPC_RETURN(bool shown);
}

IPC_API(TextDraw_SetLetterSize, uintptr_t ptr, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setLetterSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(TextDraw_SetTextSize, uintptr_t ptr, float sizeX, float sizeY)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setTextSize({ sizeX, sizeY });
	IPC_RETURN();
}

IPC_API(TextDraw_SetAlignment, uintptr_t ptr, int alignment)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setAlignment(TextDrawAlignmentTypes(alignment));
	IPC_RETURN();
}

IPC_API(TextDraw_SetColor, uintptr_t ptr, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetUseBox, uintptr_t ptr, bool use)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->useBox(use);
	IPC_RETURN();
}

IPC_API(TextDraw_SetBoxColor, uintptr_t ptr, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setBoxColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetShadow, uintptr_t ptr, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setShadow(size);
	IPC_RETURN();
}

IPC_API(TextDraw_SetOutline, uintptr_t ptr, int size)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setOutline(size);
	IPC_RETURN();
}

IPC_API(TextDraw_SetBackgroundColor, uintptr_t ptr, uint32_t colour)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setBackgroundColour(Colour::FromRGBA(colour));
	IPC_RETURN();
}

IPC_API(TextDraw_SetFont, uintptr_t ptr, int font)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setStyle(TextDrawStyle(font));
	IPC_RETURN();
}

IPC_API(TextDraw_SetSetProportional, uintptr_t ptr, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setProportional(set);
	IPC_RETURN();
}

IPC_API(TextDraw_SetSelectable, uintptr_t ptr, bool set)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setSelectable(set);
	IPC_RETURN();
}

IPC_API(TextDraw_ShowForPlayer, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->showForPlayer(player_);
	IPC_RETURN();
}

IPC_API(TextDraw_HideForPlayer, uintptr_t player, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->hideForPlayer(player_);
	IPC_RETURN();
}

IPC_API(TextDraw_ShowForAll, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	IPlayerPool* pool = OmpManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw->showForPlayer(*player);
	}
	IPC_RETURN();
}

IPC_API(TextDraw_HideForAll, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	IPlayerPool* pool = OmpManager::Get()->players;
	for (IPlayer* player : pool->entries())
	{
		textdraw->hideForPlayer(*player);
	}
	IPC_RETURN();
}

IPC_API(TextDraw_SetString, uintptr_t ptr, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setText(text);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewModel, uintptr_t ptr, int model)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setPreviewModel(model);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewRot, uintptr_t ptr, float rotationX, float rotationY, float rotationZ, float zoom)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setPreviewRotation({ rotationX, rotationY, rotationZ });
	textdraw->setPreviewZoom(zoom);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPreviewVehCol, uintptr_t ptr, int colour1, int colour2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setPreviewVehicleColour(colour1, colour2);
	IPC_RETURN();
}

IPC_API(TextDraw_SetPos, uintptr_t ptr, float x, float y)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	textdraw->setPosition({ x, y });
	IPC_RETURN();
}

IPC_API(TextDraw_GetString, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	ConstStringRef text = textdraw->getText();
	IPC_RETURN(ConstStringRef text);
}

IPC_API(TextDraw_GetLetterSize, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	const Vector2& size = textdraw->getLetterSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(TextDraw_GetTextSize, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	const Vector2& size = textdraw->getTextSize();

	auto sizeX = size.x;
	auto sizeY = size.y;
	IPC_RETURN(float sizeX, float sizeY);
}

IPC_API(TextDraw_GetPos, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	const Vector2& pos = textdraw->getPosition();

	auto x = pos.x;
	auto y = pos.y;
	IPC_RETURN(float x, float y);
}

IPC_API(TextDraw_GetColor, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto colour = textdraw->getLetterColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetBoxColor, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto colour = textdraw->getBoxColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetBackgroundColor, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto colour = textdraw->getBackgroundColour().RGBA();
	IPC_RETURN(uint32_t colour);
}

IPC_API(TextDraw_GetShadow, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto size = textdraw->getShadow();
	IPC_RETURN(int size);
}

IPC_API(TextDraw_GetOutline, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto size = textdraw->getOutline();
	IPC_RETURN(int size);
}

IPC_API(TextDraw_GetFont, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto font = static_cast<uint8_t>(textdraw->getStyle());
	IPC_RETURN(int font);
}

IPC_API(TextDraw_IsBox, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto set = textdraw->hasBox();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_IsProportional, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto set = textdraw->isProportional();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_IsSelectable, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto set = textdraw->isSelectable();
	IPC_RETURN(bool set);
}

IPC_API(TextDraw_GetAlignment, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto alignment = static_cast<uint8_t>(textdraw->getAlignment());
	IPC_RETURN(int alignment);
}

IPC_API(TextDraw_GetPreviewModel, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	auto model = textdraw->getPreviewModel();
	IPC_RETURN(int model);
}

IPC_API(TextDraw_GetPreviewRot, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	const Vector3& rotation = textdraw->getPreviewRotation();
	auto x = rotation.x;
	auto y = rotation.y;
	auto z = rotation.z;
	auto zoom = textdraw->getPreviewZoom();
	IPC_RETURN(float x, float y, float z, float zoom);
}

IPC_API(TextDraw_GetPreviewVehCol, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	Pair<int, int> colours = textdraw->getPreviewVehicleColour();
	auto colour1 = colours.first;
	auto colour2 = colours.second;
	IPC_RETURN(int colour1, int colour2);
}

IPC_API(TextDraw_SetStringForPlayer, uintptr_t ptr, uintptr_t player, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->textdraws, ITextDraw, ptr, textdraw);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	textdraw->setTextForPlayer(player_, text);
	IPC_RETURN();
}
