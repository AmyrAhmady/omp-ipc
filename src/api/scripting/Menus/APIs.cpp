#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Menu_Create, const nlohmann::json& params)
{
	IMenusComponent* component = OmpManager::Get()->menus;
	if (component)
	{
		IMenu* menu = component->create(
			params["title"], 
			{ params["x"], params["y"] }, 
			params["columns"], 
			params["column1Width"], 
			params["column2Width"]);

		if (menu)
		{
			return RETURN_VALUE(menu->getID());
		}
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Menu_Destroy, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	OmpManager::Get()->menus->release(menu->getID());
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_AddItem, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	return RETURN_VALUE(menu->addCell(params["text"], params["column"]));
}

IPC_API(Menu_SetColumnHeader, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	menu->setColumnHeader(params["headerTitle"], params["column"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_Show, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	menu->showForPlayer(player);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_Hide, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	menu->hideForPlayer(player);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_Disable, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	menu->disable();
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_DisableRow, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	menu->disableRow(params["row"]);
	return NO_DATA_SUCCESS_RETURN;
}

IPC_API(Menu_GetPlayer, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerMenuData* menuData = queryExtension<IPlayerMenuData>(player);
	if (menuData)
	{
		return RETURN_VALUE(menuData->getMenuID());
	}
	return UNDEFINED_FAILED_RETURN;
}

IPC_API(Menu_IsValid, const nlohmann::json& params)
{
	if (OmpManager::Get()->menus == nullptr)
		return "{\"ret_value\":{\"error\":\"Pool for IMenu is unavailable.\"}}"_json;

	IMenu* menu = reinterpret_cast<IMenu*>(uintptr_t(params["menu"]));
	return RETURN_VALUE(menu != nullptr);
}

IPC_API(Menu_IsDisabled, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	return RETURN_VALUE(!menu->isEnabled());
}

IPC_API(Menu_IsRowDisabled, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	return RETURN_VALUE(!menu->isRowEnabled(params["row"]));
}

IPC_API(Menu_GetColumns, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	return RETURN_VALUE(menu->getColumnCount());
}

IPC_API(Menu_GetItems, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	return RETURN_VALUE(menu->getRowCount(params["column"]));
}

IPC_API(Menu_GetPos, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	nlohmann::json ret;
	const Vector2& pos = menu->getPosition();
	ret["x"] = pos.x;
	ret["y"] = pos.y;
	return RETURN_VALUE(ret);
}

IPC_API(Menu_GetColumnWidth, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	nlohmann::json ret;
	const Vector2& widths = menu->getColumnWidths();
	ret["column1Width"] = widths.x;
	ret["column2Width"] = widths.y;
	return RETURN_VALUE(ret);
}

IPC_API(Menu_GetColumnHeader, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	nlohmann::json ret;
	ret["header"] = menu->getColumnHeader(params["column"]);
	return RETURN_VALUE(ret);
}

IPC_API(Menu_GetItem, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->menus, IMenu, params["menu"], menu);
	nlohmann::json ret;
	ret["cell"] = menu->getCell(params["column"], params["row"]);
	return RETURN_VALUE(ret);
}