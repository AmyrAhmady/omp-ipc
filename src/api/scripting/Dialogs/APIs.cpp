#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Dialog_PlayerShow, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerDialogData* playerDialogData = queryExtension<IPlayerDialogData>(player);

	if (!playerDialogData)
	{
		return NO_DATA_SUCCESS_RETURN;
	}

	if (dialog == INVALID_DIALOG_ID)
	{
		playerDialogData->hide(player);
		return RETURN_VALUE(true);
	}

	playerDialogData->show(
		player, 
		params["dialogId"] & 0xFFFF, 
		DialogStyle(params["style"]), 
		params["title"], 
		params["body"], 
		params["button1"], 
		params["button2"]);

	return RETURN_VALUE(true);
}

IPC_API(Dialog_PlayerHide, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerDialogData* playerDialogData = queryExtension<IPlayerDialogData>(player);
	if (playerDialogData && playerDialogData->getActiveID() != INVALID_DIALOG_ID)
	{
		playerDialogData->hide(player);
		return RETURN_VALUE(true);
	}
	return RETURN_VALUE(false);
}

IPC_API(Dialog_PlayerGetData, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerDialogData* playerDialogData = queryExtension<IPlayerDialogData>(player);

	int dialogId;
	DialogStyle styleVar {};
	StringView titleVar {};
	StringView bodyVar {};
	StringView button1Var {};
	StringView button2Var {};

	playerDialogData->get(dialogId, styleVar, titleVar, bodyVar, button1Var, button2Var);

	nlohmann::json ret;
	ret["dialogId"] = dialogId;
	ret["style"] = int(styleVar);
	ret["title"] = titleVar;
	ret["body"] = bodyVar;
	ret["button1"] = button1Var;
	ret["button2"] = button2Var;
	return RETURN_VALUE(ret);
}

IPC_API(Dialog_PlayerGetID, const nlohmann::json& params)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, params["player"], player);
	IPlayerDialogData* playerDialogData = queryExtension<IPlayerDialogData>(player);
	return RETURN_VALUE(playerDialogData->getActiveID());
}