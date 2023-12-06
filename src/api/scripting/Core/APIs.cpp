#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(GetTickCount)
{
	auto tick = OmpManager::Get()->core->getTickCount();
	IPC_RETURN(int tick);
}

IPC_API(GetMaxPlayers)
{
	int max = *OmpManager::Get()->core->getConfig().getInt("max_players");
	IPC_RETURN(int max);
}

IPC_API(VectorSize, float x, float y, float z)
{
	auto length = glm::length({ x, y, z });
	IPC_RETURN(float length);
}

IPC_API(asin, float value)
{
	auto degrees = std::asin(value) * 180 / M_PI;
	IPC_RETURN(float degrees);
}

IPC_API(acos, float value)
{
	auto degrees = std::acos(value) * 180 / M_PI;
	IPC_RETURN(float degrees);
}

IPC_API(atan, float value)
{
	auto degrees = std::atan(value) * 180 / M_PI;
	IPC_RETURN(float degrees);
}

IPC_API(atan2, float y, float x)
{
	auto degrees = std::atan2(y, x) * 180 / M_PI;
	IPC_RETURN(float degrees);
}

IPC_API(floatstr, ConstStringRef string)
{
	auto value = std::stof(string);
	IPC_RETURN(float value);
}

IPC_API(GetPlayerPoolSize)
{
	int highestID = -1;
	for (IPlayer* player : OmpManager::Get()->players->entries())
	{
		if (highestID < player->getID())
		{
			highestID = player->getID();
		}
	}
	IPC_RETURN(int highestID);
}

IPC_API(GetVehiclePoolSize)
{
	IVehiclesComponent* vehicles = OmpManager::Get()->vehicles;
	if (vehicles)
	{
		int highestID = -1;
		for (IVehicle* vehicle : *vehicles)
		{
			if (highestID < vehicle->getID())
			{
				highestID = vehicle->getID();
			}
		}
		IPC_RETURN(int highestID);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(GetActorPoolSize)
{
	IActorsComponent* actors = OmpManager::Get()->actors;
	if (actors)
	{
		int highestID = -1;
		for (IActor* actor : *actors)
		{
			if (highestID < actor->getID())
			{
				highestID = actor->getID();
			}
		}
		IPC_RETURN(int highestID);
	}
	return FUNCTION_FAIL_RETURN;
}
/*
// TODO: Can't return array with json

IPC_API(GetPlayers, int(DynamicArray<int>& outputPlayers))
{
	int index = -1;
	IPlayerPool* players = OmpManager::Get()->players;
	if (outputPlayers.size() < players->entries().size())
	{
		OmpManager::Get()->core->printLn(
			"There are %zu players in your server but array size used in `GetPlayers` is %zu; Use a bigger size in your script.",
			players->entries().size(),
			outputPlayers.size());
	}

	for (IPlayer* player : players->entries())
	{
		index++;
		if (index >= outputPlayers.size())
		{
			break;
		}
		outputPlayers[index] = player->getID();
	}
	index += 1;
	IPC_RETURN(int index, outputPlayers);
}

IPC_API(GetActors, int(DynamicArray<int>& outputActors))
{
	int index = -1;
	IActorsComponent* actors = OmpManager::Get()->actors;
	if (actors)
	{
		if (outputActors.size() < actors->count())
		{
			OmpManager::Get()->core->printLn(
				"There are %zu actors in your server but array size used in `GetActors` is %zu; Use a bigger size in your script.",
				actors->count(),
				outputActors.size());
		}

		for (IActor* actor : *actors)
		{
			index++;
			if (index >= outputActors.size())
			{
				break;
			}
			outputActors[index] = actor->getID();
		}
	}
	return index + 1;
}

IPC_API(GetVehicles, int(DynamicArray<int>& outputVehicles))
{
	int index = -1;
	IVehiclesComponent* vehicles = OmpManager::Get()->vehicles;
	if (vehicles)
	{
		if (outputVehicles.size() < vehicles->count())
		{
			OmpManager::Get()->core->printLn(
				"There are %zu vehicles in your server but array size used in `GetVehicles` is %zu; Use a bigger size in your script.",
				vehicles->count(),
				outputVehicles.size());
		}

		for (IVehicle* vehicle : *vehicles)
		{
			index++;
			if (index >= outputVehicles.size())
			{
				break;
			}
			outputVehicles[index] = vehicle->getID();
		}
	}
	return index + 1;
}
*/
IPC_API(print, ConstStringRef text)
{
	OmpManager::Get()->core->printLn("%s", text.c_str());
	IPC_RETURN();
}

IPC_API(IsAdminTeleportAllowed)
{
	bool allowed = *OmpManager::Get()->config->getBool("rcon.allow_teleport");
	IPC_RETURN(bool allowed);
}

IPC_API(AllowAdminTeleport, bool allow)
{
	*OmpManager::Get()->config->getBool("rcon.allow_teleport") = allow;
	IPC_RETURN();
}

IPC_API(AreAllAnimationsEnabled)
{
	bool allowed = *OmpManager::Get()->config->getBool("game.use_all_animations");
	IPC_RETURN(bool allowed);
}

IPC_API(EnableAllAnimations, bool allow)
{
	*OmpManager::Get()->config->getBool("game.use_all_animations") = allow;
	IPC_RETURN();
}

IPC_API(IsValidAnimationLibrary, ConstStringRef name)
{
	auto valid = animationLibraryValid(name, true);
	IPC_RETURN(bool valid);
}

IPC_API(AreInteriorWeaponsAllowed)
{
	bool allowed = *OmpManager::Get()->config->getBool("game.allow_interior_weapons");
	IPC_RETURN(bool allowed);
}

IPC_API(AllowInteriorWeapons, bool allow)
{
	if (allow)
	{
		*OmpManager::Get()->config->getBool("game.allow_interior_weapons") = true;
	}
	else
	{
		IPlayerPool* players = OmpManager::Get()->players;
		for (IPlayer* player : players->entries())
		{
			if (player->getInterior() && player->areWeaponsAllowed())
			{
				// Because they are allowed weapons currently this will send a full client reset.
				player->resetWeapons();
			}
		}
		// By the time the player reports having no weapons, this is set and so we remember the old
		// ones still.
		*OmpManager::Get()->config->getBool("game.allow_interior_weapons") = false;
	}
	IPC_RETURN();
}

IPC_API(BlockIpAddress, ConstStringRef ipAddress, int timeMS)
{
	if (ipAddress.empty())
	{
		return RETURN_ERROR("Empty string is passed.");
	}
	BanEntry entry(ipAddress);
	for (INetwork* network : OmpManager::Get()->core->getNetworks())
	{
		network->ban(entry, Milliseconds(timeMS));
	}
	IPC_RETURN();
}

IPC_API(UnBlockIpAddress, ConstStringRef ipAddress)
{
	BanEntry entry(ipAddress);
	for (INetwork* network : OmpManager::Get()->core->getNetworks())
	{
		network->unban(entry);
	}
	IPC_RETURN();
}

IPC_API(ConnectNPC, ConstStringRef name, ConstStringRef script)
{
	OmpManager::Get()->core->connectBot(name, script);
	IPC_RETURN();
}

IPC_API(DisableInteriorEnterExits)
{
	*OmpManager::Get()->config->getBool("game.use_entry_exit_markers") = false;
	IPC_RETURN();
}

IPC_API(DisableNameTagLOS)
{
	*OmpManager::Get()->config->getBool("game.use_nametag_los") = false;
	IPC_RETURN();
}

IPC_API(EnableTirePopping, bool enable)
{
	OmpManager::Get()->core->logLn(LogLevel::Warning, "EnableTirePopping() function is removed.");
	IPC_RETURN();
}

IPC_API(EnableZoneNames, bool enable)
{
	*OmpManager::Get()->config->getBool("game.use_zone_names") = enable;
	IPC_RETURN();
}

IPC_API(GameModeExit)
{
	OmpManager::Get()->EndMainScript();
	IPC_RETURN();
}

IPC_API(GameTextForAll, ConstStringRef msg, int time, int style)
{
	if (msg.empty())
	{
		IPC_RETURN();
	}
	OmpManager::Get()->players->sendGameTextToAll(msg, Milliseconds(time), style);
	IPC_RETURN();
}

IPC_API(HideGameTextForAll, int style)
{
	OmpManager::Get()->players->hideGameTextForAll(style);
	IPC_RETURN();
}

int getConfigOptionAsInt(ConstStringRef cvar)
{
	IConfig* config = OmpManager::Get()->config;
	auto res = config->getNameFromAlias(cvar);
	bool* v0 = nullptr;
	int* v1 = nullptr;
	if (!res.second.empty())
	{
		if (res.first)
		{
			OmpManager::Get()->core->logLn(LogLevel::Warning, "Deprecated console variable \"%s\", use \"%.*s\" instead.", cvar.c_str(), PRINT_VIEW(res.second));
		}
		if (!(v1 = config->getInt(res.second)))
		{
			v0 = config->getBool(res.second);
		}
	}
	else
	{
		if (!(v1 = config->getInt(cvar)))
		{
			v0 = config->getBool(cvar);
		}
	}
	if (v1)
	{
		return *v1;
	}
	else if (v0)
	{
		OmpManager::Get()->core->logLn(LogLevel::Warning, "Boolean console variable \"%s\" retreived as integer.", cvar.c_str());
		return *v0;
	}
	else
	{
		return 0;
	}
}

bool getConfigOptionAsBool(ConstStringRef cvar)
{
	IConfig* config = OmpManager::Get()->config;
	auto res = config->getNameFromAlias(cvar);
	bool* v0 = nullptr;
	int* v1 = nullptr;
	if (!res.second.empty())
	{
		if (res.first)
		{
			OmpManager::Get()->core->logLn(LogLevel::Warning, "Deprecated console variable \"%s\", use \"%.*s\" instead.", cvar.c_str(), PRINT_VIEW(res.second));
		}
		if (!(v0 = config->getBool(res.second)))
		{
			v1 = config->getInt(res.second);
		}
	}
	else
	{
		if (!(v0 = config->getBool(cvar)))
		{
			v1 = config->getInt(cvar);
		}
	}
	if (v0)
	{
		return *v0;
	}
	else if (v1)
	{
		OmpManager::Get()->core->logLn(LogLevel::Warning, "Integer console variable \"%s\" retreived as boolean.", cvar.c_str());
		return *v1 != 0;
	}
	else
	{
		return false;
	}
}

float getConfigOptionAsFloat(ConstStringRef cvar)
{
	IConfig* config = OmpManager::Get()->config;
	auto res = config->getNameFromAlias(cvar);
	float* var = nullptr;
	if (!res.second.empty())
	{
		if (res.first)
		{
			OmpManager::Get()->core->logLn(LogLevel::Warning, "Deprecated console variable \"%s\", use \"%.*s\" instead.", cvar.c_str(), PRINT_VIEW(res.second));
		}
		var = config->getFloat(res.second);
	}
	else
	{
		var = config->getFloat(cvar);
	}
	if (var)
	{
		return *var;
	}
	else
	{
		return 0.0f;
	}
}

int getConfigOptionAsString(ConstStringRef cvar, StringRef buffer)
{
	// Special case, converting `gamemode0` to `pawn.main_scripts[0]`.  It is the only string to
	// array change.
	IConfig* config = OmpManager::Get()->config;
	bool gm = cvar.substr(0, 8) == "gamemode";
	auto res = config->getNameFromAlias(gm ? "gamemode" : cvar);
	if (!res.second.empty())
	{
		if (res.first)
		{
			OmpManager::Get()->core->logLn(LogLevel::Warning, "Deprecated console variable \"%s\", use \"%.*s\" instead.", cvar.c_str(), PRINT_VIEW(res.second));
		}
		if (gm)
		{
			size_t i = std::stoi("0" + cvar.substr(8));
			DynamicArray<StringView> mainScripts(i + 1);
			size_t n = config->getStrings(res.second, Span<StringView>(mainScripts.data(), mainScripts.size()));
			if (i < n)
			{
				buffer = mainScripts[i];
			}
		}
		else
		{
			buffer = config->getString(res.second);
		}
	}
	else
	{
		buffer = config->getString(cvar);
	}
	return std::get<StringView>(buffer).length();
}

IPC_API(GetConsoleVarAsBool, ConstStringRef cvar)
{
	bool value = getConfigOptionAsBool(cvar);
	IPC_RETURN(bool value);
}

IPC_API(GetConsoleVarAsInt, ConstStringRef cvar)
{
	int value = getConfigOptionAsInt(cvar);
	IPC_RETURN(int value);
}

IPC_API(GetConsoleVarAsFloat, ConstStringRef cvar)
{
	float value = getConfigOptionAsFloat(cvar);
	IPC_RETURN(float value);
}

IPC_API(GetConsoleVarAsString, ConstStringRef cvar)
{
	StringRef value = "";
	int len = getConfigOptionAsString(cvar, value);
	IPC_RETURN(StringRef value, int len);
}

IPC_API(GetNetworkStats)
{
	std::stringstream stream;
	NetworkStats stats;

	for (INetwork* network : OmpManager::Get()->core->getNetworks())
	{
		if (network->getNetworkType() == ENetworkType::ENetworkType_RakNetLegacy)
		{
			stats = network->getStatistics();
		}
	}

	stream
		<< "Server Ticks: " << OmpManager::Get()->core->tickRate() << std::endl
		<< "Messages in Send buffer: " << stats.messageSendBuffer << std::endl
		<< "Messages sent: " << stats.messagesSent << std::endl
		<< "Bytes sent: " << stats.totalBytesSent << std::endl
		<< "Acks sent: " << stats.acknowlegementsSent << std::endl
		<< "Acks in send buffer: " << stats.acknowlegementsPending << std::endl
		<< "Messages waiting for ack: " << stats.messagesOnResendQueue << std::endl
		<< "Messages resent: " << stats.messageResends << std::endl
		<< "Bytes resent: " << stats.messagesTotalBytesResent << std::endl
		<< "Packetloss: " << std::setprecision(1) << std::fixed << stats.packetloss << "%" << std::endl
		<< "Messages received: " << stats.messagesReceived << std::endl
		<< "Bytes received: " << stats.bytesReceived << std::endl
		<< "Acks received: " << stats.acknowlegementsReceived << std::endl
		<< "Duplicate acks received: " << stats.duplicateAcknowlegementsReceived << std::endl
		<< "Inst. KBits per second: " << std::setprecision(1) << (stats.bitsPerSecond / 1000.0) << std::endl
		<< "KBits per second sent: " << std::setprecision(1) << (stats.bpsSent / 1000.0) << std::endl
		<< "KBits per second received: " << std::setprecision(1) << (stats.bpsReceived / 1000.0) << std::endl;

	// Scope-allocated string, copy it
	ConstStringRef output = stream.str();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(Player_GetNetworkStats, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	std::stringstream stream;
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);

	stream
		<< "Network Active: " << int(stats.isActive) << std::endl
		<< "Network State: " << stats.connectMode << std::endl
		<< "Messages in Send buffer: " << stats.messageSendBuffer << std::endl
		<< "Messages sent: " << stats.messagesSent << std::endl
		<< "Bytes sent: " << stats.totalBytesSent << std::endl
		<< "Acks sent: " << stats.acknowlegementsSent << std::endl
		<< "Acks in send buffer: " << stats.acknowlegementsPending << std::endl
		<< "Messages waiting for ack: " << stats.messagesOnResendQueue << std::endl
		<< "Messages resent: " << stats.messageResends << std::endl
		<< "Bytes resent: " << stats.messagesTotalBytesResent << std::endl
		<< "Packetloss: " << std::setprecision(1) << std::fixed << stats.packetloss << "%" << std::endl
		<< "Messages received: " << stats.messagesReceived << std::endl
		<< "Bytes received: " << stats.bytesReceived << std::endl
		<< "Acks received: " << stats.acknowlegementsReceived << std::endl
		<< "Duplicate acks received: " << stats.duplicateAcknowlegementsReceived << std::endl
		<< "Inst. KBits per second: " << std::setprecision(1) << (stats.bitsPerSecond / 1000.0) << std::endl
		<< "KBits per second sent: " << std::setprecision(1) << (stats.bpsSent / 1000.0) << std::endl
		<< "KBits per second received: " << std::setprecision(1) << (stats.bpsReceived / 1000.0) << std::endl;

	// Scope-allocated string, copy it
	ConstStringRef output = stream.str();
	IPC_RETURN(ConstStringRef output);
}

IPC_API(GetServerTickRate)
{
	int tick = OmpManager::Get()->core->tickRate();
	IPC_RETURN(int tick);
}

IPC_API(GetServerVarAsBool, ConstStringRef cvar)
{
	bool value = getConfigOptionAsBool(cvar);
	IPC_RETURN(bool value);
}

IPC_API(GetServerVarAsInt, ConstStringRef cvar)
{
	int value = getConfigOptionAsInt(cvar);
	IPC_RETURN(int value);
}

IPC_API(GetServerVarAsFloat, ConstStringRef cvar)
{
	float value = getConfigOptionAsFloat(cvar);
	IPC_RETURN(float value);
}

IPC_API(GetServerVarAsString, ConstStringRef cvar)
{
	StringRef value = "";
	int len = getConfigOptionAsString(cvar, value);
	IPC_RETURN(StringRef value, int len);
}

IPC_API(GetWeaponName, int weaponid)
{
	ConstStringRef weapon = OmpManager::Get()->core->getWeaponName(PlayerWeapon(weaponid));
	IPC_RETURN(ConstStringRef weapon);
}

IPC_API(LimitGlobalChatRadius, float chatRadius)
{
	*OmpManager::Get()->config->getBool("game.use_chat_radius") = true;
	*OmpManager::Get()->config->getFloat("game.chat_radius") = chatRadius;
	IPC_RETURN();
}

IPC_API(LimitPlayerMarkerRadius, float markerRadius)
{
	*OmpManager::Get()->config->getBool("game.use_player_marker_draw_radius") = true;
	*OmpManager::Get()->config->getFloat("game.player_marker_draw_radius") = markerRadius;
	IPC_RETURN();
}

IPC_API(NetStats_BytesReceived, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int bytes = stats.bytesReceived;
	IPC_RETURN(int bytes);
}

IPC_API(NetStats_BytesSent, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int bytes = stats.totalBytesSent;
	IPC_RETURN(int bytes);
}

IPC_API(NetStats_ConnectionStatus, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int status = stats.connectMode;
	IPC_RETURN(int status);
}

IPC_API(NetStats_GetConnectedTime, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int milliseconds = stats.connectionElapsedTime;
	IPC_RETURN(int milliseconds);
}

IPC_API(NetStats_GetIpPort, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	PeerNetworkData data = player_->getNetworkData();
	PeerAddress::AddressString addressString;
	if (PeerAddress::ToString(data.networkID.address, addressString))
	{
		String ip_port((StringView(addressString)));
		ip_port += ":";
		ip_port += std::to_string(data.networkID.port);
		// Scope-allocated string, copy it
		ConstStringRef output = ip_port;
		IPC_RETURN(ConstStringRef output);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(NetStats_MessagesReceived, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int received = stats.messagesReceived;
	IPC_RETURN(int received);
}

IPC_API(NetStats_MessagesRecvPerSecond, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int received = stats.messagesReceivedPerSecond;
	IPC_RETURN(int received);
}

IPC_API(NetStats_MessagesSent, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	int sent = stats.messagesSent;
	IPC_RETURN(int sent);
}

IPC_API(NetStats_PacketLossPercent, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	NetworkStats stats = player_->getNetworkData().network->getStatistics(&player_);
	auto packetLoss = stats.packetloss;
	IPC_RETURN(float packetLoss);
}

IPC_API(SendPlayerMessageToAll, uintptr_t sender, ConstStringRef message)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, sender, sender_);
	OmpManager::Get()->players->sendChatMessageToAll(sender_, message);
	IPC_RETURN();
}

IPC_API(SendRconCommand, ConstStringRef command)
{
	IConsoleComponent* console = OmpManager::Get()->console;
	if (console)
	{
		console->send(command);
	}
	IPC_RETURN();
}

IPC_API(SetDeathDropAmount, int amount)
{
	*OmpManager::Get()->config->getInt("game.death_drop_amount") = amount;
	IPC_RETURN();
}

IPC_API(SetGameModeText, ConstStringRef string)
{
	OmpManager::Get()->core->setData(SettableCoreDataType::ModeText, string);
	IPC_RETURN();
}

IPC_API(SetGravity, float gravity)
{
	OmpManager::Get()->core->setGravity(gravity);
	IPC_RETURN();
}

IPC_API(GetGravity)
{
	float gravity = OmpManager::Get()->core->getGravity();
	IPC_RETURN(float gravity);
}

IPC_API(SetNameTagDrawDistance, float distance)
{
	*OmpManager::Get()->config->getFloat("game.nametag_draw_radius") = distance;
	IPC_RETURN();
}

IPC_API(SetTeamCount, int count)
{
	IPC_RETURN();
}

IPC_API(SetWeather, int weatherid)
{
	OmpManager::Get()->core->setWeather(weatherid);
	IPC_RETURN();
}

IPC_API(SetWorldTime, int hour)
{
	OmpManager::Get()->core->setWorldTime(Hours(hour));
	IPC_RETURN();
}

IPC_API(ShowNameTags, bool show)
{
	*OmpManager::Get()->config->getBool("game.use_nametags") = show;
	IPC_RETURN();
}

IPC_API(ShowPlayerMarkers, int mode)
{
	*OmpManager::Get()->config->getInt("game.player_marker_mode") = mode;
	IPC_RETURN();
}

IPC_API(UsePlayerPedAnims)
{
	*OmpManager::Get()->config->getBool("game.use_player_ped_anims") = true;
	IPC_RETURN();
}

IPC_API(GetWeather)
{
	int weatherid = *OmpManager::Get()->config->getInt("game.weather");
	IPC_RETURN(int weatherid);
}

IPC_API(GetWorldTime)
{
	int hour = *OmpManager::Get()->config->getInt("game.time");
	IPC_RETURN(int hour);
}

IPC_API(ToggleChatTextReplacement, bool enable)
{
	*OmpManager::Get()->config->getBool("chat_input_filter") = enable;
	IPC_RETURN();
}

IPC_API(ChatTextReplacementToggled)
{
	bool toggled = *OmpManager::Get()->config->getBool("chat_input_filter");
	IPC_RETURN(bool toggled);
}

IPC_API(IsValidNickName, ConstStringRef name)
{
	auto valid = OmpManager::Get()->players->isNameValid(name);
	IPC_RETURN(bool valid);
}

IPC_API(AllowNickNameCharacter, int character, bool allow)
{
	OmpManager::Get()->players->allowNickNameCharacter(character, allow);
	IPC_RETURN();
}

IPC_API(IsNickNameCharacterAllowed, char character)
{
	bool allowed = OmpManager::Get()->players->isNickNameCharacterAllowed(character);
	IPC_RETURN(bool allowed);
}

IPC_API(ClearBanList)
{
	ICore* core = OmpManager::Get()->core;
	if (!core)
	{
		return FUNCTION_FAIL_RETURN;
	}

	core->getConfig().clearBans();
	IPC_RETURN();
}

IPC_API(IsBanned, ConstStringRef ip)
{
	ICore* core = OmpManager::Get()->core;
	if (!core)
	{
		return FUNCTION_FAIL_RETURN;
	}
	BanEntry entry(ip);
	bool isBanned = core->getConfig().isBanned(entry);
	IPC_RETURN(bool isBanned);
}

IPC_API(GetWeaponSlot, uint8_t weapon)
{
	int slot = WeaponSlotData { weapon }.slot();
	IPC_RETURN(int slot);
}

IPC_API(AddServerRule, ConstStringRef name, ConstStringRef value)
{
	ICore* core = OmpManager::Get()->core;
	if (!core)
	{
		return FUNCTION_FAIL_RETURN;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			query->addRule(name, value);
			IPC_RETURN();
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(IsValidServerRule, ConstStringRef name)
{
	ICore* core = OmpManager::Get()->core;
	if (!core)
	{
		return FUNCTION_FAIL_RETURN;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			bool valid = query->isValidRule(name);
			IPC_RETURN(bool valid);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(RemoveServerRule, ConstStringRef name)
{
	ICore* core = OmpManager::Get()->core;
	if (!core)
	{
		return FUNCTION_FAIL_RETURN;
	}

	for (INetwork* network : core->getNetworks())
	{
		INetworkQueryExtension* query = queryExtension<INetworkQueryExtension>(network);

		if (query)
		{
			query->removeRule(name);
			IPC_RETURN();
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(GetRunningTimers)
{
	ITimersComponent* timers = OmpManager::Get()->timers;
	int count = timers == nullptr ? 0 : timers->count();
	IPC_RETURN(int count);
}
