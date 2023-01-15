#pragma once
#include "../Manager.hpp"
#include "../../../message/Socket.hpp"
#include "sdk.hpp"

class PlayerEvents :
	public PlayerConnectEventHandler, public PlayerUpdateEventHandler, public PlayerSpawnEventHandler,
	public PlayerStreamEventHandler, public PlayerTextEventHandler, public PlayerShotEventHandler,
	public PlayerChangeEventHandler, public PlayerDamageEventHandler, public PlayerClickEventHandler,
	public PlayerCheckEventHandler,
	public Singleton<PlayerEvents>
{
public:
	void onPlayerConnect(IPlayer& player) override
	{
		nlohmann::json args;
		args["player"] = uintptr_t(&player);
		MessageSocket::ProcessEvent("onConnect", args);
	}

	void onPlayerSpawn(IPlayer& player) override
	{

	}

	bool onPlayerCommandText(IPlayer& player, StringView cmdtext) override
	{
		bool ret = false;
		return ret;
	}

	void onPlayerKeyStateChange(IPlayer& player, uint32_t newKeys, uint32_t oldKeys) override
	{

	}

	void onIncomingConnection(IPlayer& player, StringView ipAddress, unsigned short port) override
	{

	}

	void onPlayerDisconnect(IPlayer& player, PeerDisconnectReason reason) override
	{

	}

	bool onPlayerRequestSpawn(IPlayer& player) override
	{
		bool ret = false;
		return ret;
	}

	void onPlayerStreamIn(IPlayer& player, IPlayer& forPlayer) override
	{

	}

	void onPlayerStreamOut(IPlayer& player, IPlayer& forPlayer) override
	{

	}

	bool onPlayerText(IPlayer& player, StringView message) override
	{
		bool ret = false;
		return ret;
	}

	bool onPlayerShotMissed(IPlayer& player, const PlayerBulletData& bulletData) override
	{
		bool ret = false;
		return ret;
	}

	bool onPlayerShotPlayer(IPlayer& player, IPlayer& target, const PlayerBulletData& bulletData) override
	{
		bool ret = false;
		return ret;
	}

	bool onPlayerShotVehicle(IPlayer& player, IVehicle& target, const PlayerBulletData& bulletData) override
	{
		bool ret = false;
		return ret;
	}

	bool onPlayerShotObject(IPlayer& player, IObject& target, const PlayerBulletData& bulletData) override
	{
		bool ret = false;
		return ret;
	}

	bool onPlayerShotPlayerObject(IPlayer& player, IPlayerObject& target, const PlayerBulletData& bulletData) override
	{
		bool ret = false;
		return ret;
	}

	void onPlayerDeath(IPlayer& player, IPlayer* killer, int reason) override
	{

	}

	void onPlayerTakeDamage(IPlayer& player, IPlayer* from, float amount, unsigned weapon, BodyPart part) override
	{

	}

	void onPlayerGiveDamage(IPlayer& player, IPlayer& to, float amount, unsigned weapon, BodyPart part) override
	{

	}

	void onPlayerInteriorChange(IPlayer& player, unsigned newInterior, unsigned oldInterior) override
	{

	}

	void onPlayerStateChange(IPlayer& player, PlayerState newState, PlayerState oldState) override
	{

	}

	void onPlayerClickMap(IPlayer& player, Vector3 pos) override
	{
		;
	}

	void onPlayerClickPlayer(IPlayer& player, IPlayer& clicked, PlayerClickSource source) override
	{

	}

	void onClientCheckResponse(IPlayer& player, int actionType, int address, int results) override
	{

	}

	bool onPlayerUpdate(IPlayer& player, TimePoint now) override
	{
		bool ret = true;
		return ret;
	}
};