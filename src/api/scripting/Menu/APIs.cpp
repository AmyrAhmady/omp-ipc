#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Menu_Create, ConstStringRef title, uint32_t columns, float x, float y, float column1Width, float column2Width)
{
	IMenusComponent* component = OmpManager::Get()->menus;
	if (component)
	{
		IMenu* menu = component->create(title, { x, y }, columns, column1Width, column2Width);
		if (menu)
		{
			auto id = menu->getID();
			auto ptr = reinterpret_cast<uintptr_t>(menu);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Menu_Destroy, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	OmpManager::Get()->menus->release(menu->GetID());
	IPC_RETURN();
}

IPC_API(Menu_AddItem, uintptr_t ptr, uint8_t column, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	auto index = menu->addCell(text, column);
	IPC_RETURN(int index);
}

IPC_API(Menu_SetColumnHeader, uintptr_t ptr, uint8_t column, ConstStringRef headerTitle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	menu->setColumnHeader(headerTitle, column);
	IPC_RETURN();
}

IPC_API(Menu_ShowForPlayer, uintptr_t ptr, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	menu->showForPlayer(player_);
	IPC_RETURN();
}

IPC_API(Menu_HideForPlayer, uintptr_t ptr, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	menu->hideForPlayer(player_);
	IPC_RETURN();
}

IPC_API(Menu_Disable, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	menu->disable();
	IPC_RETURN();
}

IPC_API(Menu_DisableRow, uintptr_t ptr, uint8_t row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	menu->disableRow(row);
	IPC_RETURN();
}

IPC_API(Player_GetMenu, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerMenuData* menuData = queryExtension<IPlayerMenuData>(player_);
	if (menuData)
	{
		auto id = menuData->getMenuID();
		IPC_RETURN(int id);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Menu_IsValid, uintptr_t ptr)
{
	if (OmpManager::Get()->menus == nullptr)
		return RETURN_ERROR("Pool for IMenu is unavailable.");

	IMenu* menu = reinterpret_cast<IMenu*>(ptr);
	auto valid = menu != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Menu_IsDisabled, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	auto disabled = !menu->isEnabled();
	IPC_RETURN(bool disabled);
}

IPC_API(Menu_IsRowDisabled, uintptr_t ptr, int row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	auto disabled = !menu->isRowEnabled(row);
	IPC_RETURN(bool disabled);
}

IPC_API(Menu_GetColumns, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	auto columns = menu->getColumnCount();
	IPC_RETURN(int columns);
}

IPC_API(Menu_GetItems, uintptr_t ptr, int column)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	auto rows = menu->getRowCount(column);
	IPC_RETURN(int rows);
}

IPC_API(Menu_GetPos, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	const Vector2& pos = menu->getPosition();
	auto x = pos.x;
	auto y = pos.y;
	IPC_RETURN(float x, float y);
}

IPC_API(Menu_GetColumnWidth, uintptr_t ptr)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	const Vector2& widths = menu->getColumnWidths();
	auto column1Width = widths.x;
	auto column2Width = widths.y;
	IPC_RETURN(float column1Width, float column2Width);
}

IPC_API(Menu_GetColumnHeader, uintptr_t ptr, int column)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	ConstStringRef header = menu->getColumnHeader(column);
	IPC_RETURN(ConstStringRef header);
}

IPC_API(Menu_GetItem, uintptr_t ptr, int column, int row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, ptr, menu);
	ConstStringRef cell = menu->getCell(column, row);
	IPC_RETURN(ConstStringRef cell);
}
