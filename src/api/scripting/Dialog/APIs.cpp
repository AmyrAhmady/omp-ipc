#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(Dialog_Show, uintptr_t player, int dialog, int style, ConstStringRef title, ConstStringRef body, ConstStringRef button1, ConstStringRef button2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);

	if (!data)
	{
		IPC_RETURN();
	}

	if (dialog == INVALID_DIALOG_ID)
	{
		static bool warned = false;
		if (!warned)
		{
			OmpManager::Get()->core->logLn(LogLevel::Warning, "Invalid dialog ID %d used.  Use `Dialog_Hide()`.", dialog);
			warned = true;
		}

		data->hide(player_);
		IPC_RETURN();
	}

	data->show(player_, dialog & 0xFFFF, DialogStyle(style), title, body, button1, button2);
	IPC_RETURN();
}

IPC_API(Player_GetDialog, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);
	auto dialog = data->getActiveID();
	IPC_API(int dialog);
}

IPC_API(Player_GetDialogData, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerDialogData* data = queryExtension<IPlayerDialogData>(player_);
	DialogStyle styleVar {};
	StringView titleVar {};
	StringView bodyVar {};
	StringView button1Var {};
	StringView button2Var {};
	int dialogid;
	data->get(dialogid, styleVar, titleVar, bodyVar, button1Var, button2Var);
	int style = int(styleVar);
	ConstStringRef title = titleVar;
	ConstStringRef body = bodyVar;
	ConstStringRef button1 = button1Var;
	ConstStringRef button2 = button2Var;
	IPC_RETURN(int dialogid, int style, ConstStringRef title, ConstStringRef body, ConstStringRef button1, ConstStringRef button2);
}

IPC_API(Dialog_Hide, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerDialogData* dialog = queryExtension<IPlayerDialogData>(player_);
	if (dialog && dialog->getActiveID() != INVALID_DIALOG_ID)
	{
		dialog->hide(player_);
		IPC_RETURN();
	}
	IPC_RETURN();
}