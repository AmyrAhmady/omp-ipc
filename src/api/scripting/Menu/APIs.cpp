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

IPC_API(Menu_Destroy, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	OmpManager::Get()->menus->release(menu_->getID());
	IPC_RETURN();
}

IPC_API(Menu_AddItem, uintptr_t menu, uint8_t column, ConstStringRef text)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto index = menu_->addCell(text, column);
	IPC_RETURN(int index);
}

IPC_API(Menu_SetColumnHeader, uintptr_t menu, uint8_t column, ConstStringRef headerTitle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	menu_->setColumnHeader(headerTitle, column);
	IPC_RETURN();
}

IPC_API(Menu_ShowForPlayer, uintptr_t menu, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	menu_->showForPlayer(*player_);
	IPC_RETURN();
}

IPC_API(Menu_HideForPlayer, uintptr_t menu, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	menu_->hideForPlayer(*player_);
	IPC_RETURN();
}

IPC_API(Menu_Disable, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	menu_->disable();
	IPC_RETURN();
}

IPC_API(Menu_DisableRow, uintptr_t menu, uint8_t row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	menu_->disableRow(row);
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

IPC_API(Menu_IsValid, uintptr_t menu)
{
	if (OmpManager::Get()->menus == nullptr)
	{
		return FUNCTION_FAIL_RETURN;
	}

	IMenu* menu_ = reinterpret_cast<IMenu*>(menu);
	auto valid = menu_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Menu_IsDisabled, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto disabled = !menu_->isEnabled();
	IPC_RETURN(bool disabled);
}

IPC_API(Menu_IsRowDisabled, uintptr_t menu, int row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto disabled = !menu_->isRowEnabled(row);
	IPC_RETURN(bool disabled);
}

IPC_API(Menu_GetColumns, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto columns = menu_->getColumnCount();
	IPC_RETURN(int columns);
}

IPC_API(Menu_GetItems, uintptr_t menu, int column)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto rows = menu_->getRowCount(column);
	IPC_RETURN(int rows);
}

IPC_API(Menu_GetPos, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto pos = menu_->getPosition();
	auto x = pos.x;
	auto y = pos.y;
	IPC_RETURN(float x, float y);
}

IPC_API(Menu_GetColumnWidth, uintptr_t menu)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	auto widths = menu_->getColumnWidths();
	auto column1Width = widths.x;
	auto column2Width = widths.y;
	IPC_RETURN(float column1Width, float column2Width);
}

IPC_API(Menu_GetColumnHeader, uintptr_t menu, int column)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	ConstStringRef header = menu_->getColumnHeader(column).data();
	IPC_RETURN(ConstStringRef header);
}

IPC_API(Menu_GetItem, uintptr_t menu, int column, int row)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, menu, menu_);
	ConstStringRef cell = menu_->getCell(column, row).data();
	IPC_RETURN(ConstStringRef cell);
}
