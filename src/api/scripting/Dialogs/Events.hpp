#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

struct DialogEvents : public PlayerDialogEventHandler, public Singleton<DialogEvents>
{
	void onDialogResponse(IPlayer& player, int dialogId, DialogResponse response, int listItem, StringView inputText) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		args["dialogId"] = dialogId;
		args["response"] = int(response);
		args["listItem"] = listItem;
		args["inputText"] = inputText;
		MessageSocket::ProcessEvent("dialogResponse", args);
	}
};
