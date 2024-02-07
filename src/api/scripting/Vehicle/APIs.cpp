#include "../../../message/Handler.hpp"
#include "../Manager.hpp"
#include <Server/Components/Vehicles/vehicle_components.hpp>
#include <Server/Components/Vehicles/vehicle_models.hpp>
#include <Server/Components/Vehicles/vehicle_colours.hpp>
#include <Server/Components/Vehicles/vehicle_seats.hpp>

IPC_API(Vehicle_Create, int modelid, float x, float y, float z, float rotation, int colour1, int colour2, int respawnDelay, bool addSiren)
{
	IVehiclesComponent* vehicles = OmpManager().Get()->vehicles;
	if (vehicles)
	{
		IVehicle* vehicle = vehicles->create(false, modelid, { x, y, z }, rotation, colour1, colour2, Seconds(respawnDelay), addSiren);
		if (vehicle)
		{
			auto id = vehicle->getID();
			auto ptr = reinterpret_cast<uintptr_t>(vehicle);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Vehicle_GetMaxPassengerSeats, int modelid)
{
	int seats = Impl::getVehiclePassengerSeats(modelid);
	IPC_RETURN(int seats);
}

IPC_API(Vehicle_Destroy, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	OmpManager().Get()->vehicles->release(vehicle_->getID());
	IPC_RETURN();
}

IPC_API(Vehicle_IsStreamedIn, uintptr_t vehicle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	bool streamed = vehicle_->isStreamedInForPlayer(*player_);
	IPC_RETURN(bool streamed);
}

IPC_API(Vehicle_GetPos, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const Vector3& pos = vehicle_->getPosition();

	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Vehicle_SetPos, uintptr_t vehicle, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setPosition({ x, y, z });
	IPC_RETURN();
}

IPC_API(Vehicle_GetZAngle, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	float angle = vehicle_->getZAngle();
	IPC_RETURN(float angle);
}

IPC_API(Vehicle_GetRotationQuat, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	glm::quat rotQuat = vehicle_->getRotation().q;
	float w = rotQuat.w;
	float x = rotQuat.x;
	float y = rotQuat.y;
	float z = rotQuat.z;
	IPC_RETURN(float w, float x, float y, float z);
}

IPC_API(Vehicle_GetDistanceFromPoint, uintptr_t vehicle, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	float distance = glm::distance(vehicle_->getPosition(), { x, y, z });
	IPC_RETURN(float distance);
}

IPC_API(Vehicle_SetZAngle, uintptr_t vehicle, float angle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setZAngle(angle);
	IPC_RETURN();
}

IPC_API(Vehicle_SetParamsForPlayer, uintptr_t vehicle, uintptr_t player, int objective, int doors)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	VehicleParams params = vehicle_->getParams();
	params.objective = objective;
	params.doors = doors;
	vehicle_->setParamsForPlayer(*player_, params);
	IPC_RETURN();
}

IPC_API(Vehicle_UseManualEngineAndLights)
{
	*OmpManager().Get()->core->getConfig().getBool("game.use_manual_engine_and_lights") = true;
	IPC_RETURN();
}

IPC_API(Vehicle_SetParamsEx, uintptr_t vehicle, int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	VehicleParams params = vehicle_->getParams();
	params.engine = engine;
	params.lights = lights;
	params.alarm = alarm;
	params.doors = doors;
	params.bonnet = bonnet;
	params.boot = boot;
	params.objective = objective;
	vehicle_->setParams(params);
	IPC_RETURN();
}

IPC_API(Vehicle_GetParamsEx, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const VehicleParams& params = vehicle_->getParams();
	int engine = params.engine;
	int lights = params.lights;
	int alarm = params.alarm;
	int doors = params.doors;
	int bonnet = params.bonnet;
	int boot = params.boot;
	int objective = params.objective;
	IPC_RETURN(int engine, int lights, int alarm, int doors, int bonnet, int boot, int objective);
}

IPC_API(Vehicle_GetParamsSirenState, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int state = vehicle_->getParams().siren;
	IPC_RETURN(int state);
}

IPC_API(Vehicle_SetParamsCarDoors, uintptr_t vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	VehicleParams params = vehicle_->getParams();
	params.doorDriver = frontLeft;
	params.doorPassenger = frontRight;
	params.doorBackLeft = rearLeft;
	params.doorBackRight = rearRight;
	vehicle_->setParams(params);
	IPC_RETURN();
}

IPC_API(Vehicle_GetParamsCarDoors, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const VehicleParams& params = vehicle_->getParams();
	int frontLeft = params.doorDriver;
	int frontRight = params.doorPassenger;
	int rearLeft = params.doorBackLeft;
	int rearRight = params.doorBackRight;
	IPC_RETURN(int frontLeft, int frontRight, int rearLeft, int rearRight);
}

IPC_API(Vehicle_SetParamsCarWindows, uintptr_t vehicle, int frontLeft, int frontRight, int rearLeft, int rearRight)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	VehicleParams params = vehicle_->getParams();
	params.windowDriver = frontLeft;
	params.windowPassenger = frontRight;
	params.windowBackLeft = rearLeft;
	params.windowBackRight = rearRight;
	vehicle_->setParams(params);
	IPC_RETURN();
}

IPC_API(Vehicle_GetParamsCarWindows, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const VehicleParams& params = vehicle_->getParams();
	int frontLeft = params.windowDriver;
	int frontRight = params.windowPassenger;
	int rearLeft = params.windowBackLeft;
	int rearRight = params.windowBackRight;
	IPC_RETURN(int frontLeft, int frontRight, int rearLeft, int rearRight);
}

IPC_API(Vehicle_SetToRespawn, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->respawn();
	IPC_RETURN();
}

IPC_API(Vehicle_LinkToInterior, uintptr_t vehicle, int interiorid)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setInterior(interiorid);
	IPC_RETURN();
}

IPC_API(Vehicle_AddComponent, uintptr_t vehicle, int componentid)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->addComponent(componentid);
	IPC_RETURN();
}

IPC_API(Vehicle_RemoveComponent, uintptr_t vehicle, int componentid)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->removeComponent(componentid);
	IPC_RETURN();
}

IPC_API(Vehicle_ChangeColour, uintptr_t vehicle, int colour1, int colour2)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setColour(colour1, colour2);
	IPC_RETURN();
}

IPC_API(Vehicle_ChangePaintjob, uintptr_t vehicle, int paintjobid)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setPaintJob(paintjobid);
	IPC_RETURN();
}

IPC_API(Vehicle_SetHealth, uintptr_t vehicle, float health)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setHealth(health);
	IPC_RETURN();
}

IPC_API(Vehicle_GetHealth, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	float health = vehicle_->getHealth();
	IPC_RETURN(float health);
}

IPC_API(Vehicle_AttachTrailer, uintptr_t trailer, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, trailer, trailer_);
	vehicle_->attachTrailer(*trailer_);
	IPC_RETURN();
}

IPC_API(Vehicle_DetachTrailer, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->detachTrailer();
	IPC_RETURN();
}

IPC_API(Vehicle_IsTrailerAttached, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	bool attached = vehicle_->getTrailer() != nullptr;
	IPC_RETURN(bool attached);
}

IPC_API(Vehicle_GetTrailer, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IVehicle* trailer = vehicle_->getTrailer();
	if (trailer)
	{
		auto id = trailer->getID();
		auto ptr = reinterpret_cast<uintptr_t>(trailer);
		IPC_RETURN(int id, uintptr_t ptr);
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Vehicle_SetNumberPlate, uintptr_t vehicle, ConstStringRef numberPlate)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setPlate(numberPlate);
	IPC_RETURN();
}

IPC_API(Vehicle_GetModel, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int model = vehicle_->getModel();
	IPC_RETURN(int model);
}

IPC_API(Vehicle_GetComponentInSlot, uintptr_t vehicle, int slot)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int component = vehicle_->getComponentInSlot(slot);
	IPC_RETURN(int component);
}

IPC_API(Vehicle_GetComponentType, int componentid)
{
	int type = Impl::getVehicleComponentSlot(componentid);
	IPC_RETURN(int type);
}

IPC_API(Vehicle_CanHaveComponent, int modelid, int componentid)
{
	bool valid = Impl::isValidComponentForVehicleModel(modelid, componentid);
	IPC_RETURN(bool valid);
}

IPC_API(Vehicle_GetRandomColourPair, int modelid)
{
	int colour1;
	int colour2;
	int colour3;
	int colour4;
	Impl::getRandomVehicleColour(modelid, colour1, colour2, colour3, colour4);
	IPC_RETURN(int colour1, int colour2, int colour3, int colour4);
}

IPC_API(Vehicle_ColourIndexToColour, int colourIndex, int alpha)
{
	int colour = Impl::carColourIndexToColour(colourIndex, alpha);
	IPC_RETURN(int colour);
}

IPC_API(Vehicle_Repair, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->repair();
	IPC_RETURN();
}

IPC_API(Vehicle_GetVelocity, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const Vector3& velocity = vehicle_->getVelocity();
	float x = velocity.x;
	float y = velocity.y;
	float z = velocity.z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Vehicle_SetVelocity, uintptr_t vehicle, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setVelocity({ x, y, z });
	IPC_RETURN();
}

IPC_API(Vehicle_SetAngularVelocity, uintptr_t vehicle, float x, float y, float z)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setAngularVelocity({ x, y, z });
	IPC_RETURN();
}

IPC_API(Vehicle_GetDamageStatus, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int panels;
	int doors;
	int lights;
	int tires;
	vehicle_->getDamageStatus(panels, doors, lights, tires);
	IPC_RETURN(int panels, int doors, int lights, int tires);
}

IPC_API(Vehicle_UpdateDamageStatus, uintptr_t vehicle, int panels, int doors, int lights, int tires)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setDamageStatus(panels, doors, lights, tires);
	IPC_RETURN();
}

IPC_API(Vehicle_GetModelInfo, int vehiclemodel, int infotype)
{
	// TODO
	Vector3* pos = { };
	Impl::getVehicleModelInfo(vehiclemodel, VehicleModelInfoType(infotype), *pos);
	float x = pos->x;
	float y = pos->y;
	float z = pos->z;
	IPC_RETURN(float x, float y, float z);
}

IPC_API(Vehicle_SetVirtualWorld, uintptr_t vehicle, int virtualWorld)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setVirtualWorld(virtualWorld);
	IPC_RETURN();
}

IPC_API(Vehicle_GetVirtualWorld, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int virtualWorld = vehicle_->getVirtualWorld();
	IPC_RETURN(int virtualWorld);
}

IPC_API(Vehicle_GetLandingGearState, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int state = !vehicle_->getLandingGearState();
	IPC_RETURN(int state);
}

IPC_API(Vehicle_IsValid, uintptr_t vehicle)
{
	if (OmpManager::Get()->vehicles == nullptr)
		return RETURN_ERROR("Pool for IVehicle is unavailable.");

	IActor* vehicle_ = reinterpret_cast<IActor*>(vehicle);
	auto valid = vehicle_ != nullptr;
	IPC_RETURN(bool valid);
}

IPC_API(Vehicle_AddStatic, int modelid, float x, float y, float z, float angle, int colour1, int colour2)
{
	IVehiclesComponent* vehicles = OmpManager().Get()->vehicles;
	if (vehicles)
	{
		IVehicle* vehicle = vehicles->create(true, modelid, { x, y, z }, angle, colour1, colour2, Seconds(120), false);
		if (vehicle)
		{
			auto id = vehicle->getID();
			auto ptr = reinterpret_cast<uintptr_t>(vehicle);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Vehicle_AddStaticEx, int modelid, float x, float y, float z, float angle, int colour1, int colour2, int respawnDelay, bool addSiren)
{
	IVehiclesComponent* vehicles = OmpManager().Get()->vehicles;
	if (vehicles)
	{
		IVehicle* vehicle = vehicles->create(true, modelid, { x, y, z }, angle, colour1, colour2, Seconds(respawnDelay), addSiren);
		if (vehicle)
		{
			auto id = vehicle->getID();
			auto ptr = reinterpret_cast<uintptr_t>(vehicle);
			IPC_RETURN(int id, uintptr_t ptr);
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Vehicle_EnableFriendlyFire)
{
	*OmpManager::Get()->core->getConfig().getBool("game.use_vehicle_friendly_fire") = true;
	IPC_RETURN();
}

IPC_API(Vehicle_GetSpawnInfo, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const VehicleSpawnData& data = vehicle_->getSpawnData();

	float x = data.position.x;
	float y = data.position.y;
	float z = data.position.z;
	float rotation = data.zRotation;
	int colour1 = data.colour1;
	int colour2 = data.colour2;
	IPC_RETURN(float x, float y, float z, float rotation, int colour1, int colour2);
}

IPC_API(Vehicle_SetSpawnInfo, uintptr_t vehicle, int modelid, float x, float y, float z, float rotation, int colour1, int colour2, int respawn_time, int interior)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	const VehicleSpawnData& data = vehicle_->getSpawnData();

	vehicle_->setSpawnData({ respawn_time >= -1 ? Seconds(respawn_time) : data.respawnDelay, modelid, { x, y, z }, rotation, colour1, colour2, data.siren, interior != -2 ? interior : data.interior });
	IPC_RETURN();
}

IPC_API(Vehicle_GetModelCount, int modelid)
{
	if (modelid < 400 || modelid > 611)
		return FUNCTION_FAIL_RETURN;

	auto& models = OmpManager::Get()->vehicles->models();
	int count = models[modelid - 400];
	IPC_RETURN(int count);
}

IPC_API(Vehicle_GetModelsUsed)
{
	auto& vehicle_models = OmpManager::Get()->vehicles->models();

	int models = std::count_if(vehicle_models.begin(), vehicle_models.end(), [](uint8_t model_instances)
		{
			return model_instances > 0;
		});
	IPC_RETURN(int models);
}

IPC_API(Vehicle_GetPaintjob, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int paintjob = vehicle_->getPaintJob();
	IPC_RETURN(int paintjob);
}

IPC_API(Vehicle_GetColour, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	Pair<int, int> colors = vehicle_->getColour();

	int colour1 = colors.first;
	int colour2 = colors.second;
	IPC_RETURN(int colour1, int colour2);
}

IPC_API(Vehicle_GetInterior, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int interior = vehicle_->getInterior();
	IPC_RETURN(int interior);
}

IPC_API(Vehicle_GetNumberPlate, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	StringView numberPlate = vehicle_->getPlate();
	IPC_RETURN(ConstStringRef numberPlate);
}

IPC_API(Vehicle_SetRespawnDelay, uintptr_t vehicle, int respawn_delay)
{
	if (respawn_delay < -1) {
		return FUNCTION_FAIL_RETURN;
	}

	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setRespawnDelay(Seconds(respawn_delay));
	IPC_RETURN();
}

IPC_API(Vehicle_GetRespawnDelay, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int delay = vehicle_->getRespawnDelay().count();
	IPC_RETURN(int delay);
}

IPC_API(Vehicle_GetCab, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IVehicle* cab = vehicle_->getCab();

	if (cab == nullptr)
	{
		return FUNCTION_FAIL_RETURN;
	}

	auto id = cab->getID();
	auto ptr = reinterpret_cast<uintptr_t>(cab);
	IPC_RETURN(int id, uintptr_t ptr);
}

IPC_API(Vehicle_GetTower, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IVehicle* cab = vehicle_->getCab();

	if (cab == nullptr)
	{
		return FUNCTION_FAIL_RETURN;
	}

	auto id = cab->getID();
	auto ptr = reinterpret_cast<uintptr_t>(cab);
	IPC_RETURN(int id, uintptr_t ptr);
}

IPC_API(Vehicle_GetOccupiedTick, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int tick = std::chrono::duration_cast<Milliseconds>(Time::now() - vehicle_->getLastOccupiedTime()).count();
	IPC_RETURN(int tick);
}

IPC_API(Vehicle_GetRespawnTick, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int tick = std::chrono::duration_cast<Milliseconds>(Time::now() - vehicle_->getLastSpawnTime()).count();
	IPC_RETURN(int tick);
}

IPC_API(Vehicle_HasBeenOccupied, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	bool occupied = vehicle_->hasBeenOccupied();
	IPC_RETURN(bool occupied);
}

IPC_API(Vehicle_IsOccupied, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	bool occupied = vehicle_->isOccupied();
	IPC_RETURN(bool occupied);
}

IPC_API(Vehicle_IsDead, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	bool dead = vehicle_->isDead();
	IPC_RETURN(bool dead);
}

IPC_API(Vehicle_SetParamsSirenState, uintptr_t vehicle, bool siren_state)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	VehicleParams params = vehicle_->getParams();
	params.siren = siren_state;

	vehicle_->setParams(params);
	IPC_RETURN();
}

IPC_API(Vehicle_ToggleSirenEnabled, uintptr_t vehicle, bool status)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	vehicle_->setSiren(status);
	IPC_RETURN();
}

IPC_API(Vehicle_IsSirenEnabled, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	bool enabled = vehicle_->getSpawnData().siren;
	IPC_RETURN(bool enabled);
}

IPC_API(Vehicle_GetLastDriver, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int lastDriver = vehicle_->getLastDriverPoolID();
	IPC_RETURN(int lastDriver);
}

IPC_API(Vehicle_GetDriver, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IPlayer* driver = vehicle_->getDriver();

	if (!driver)
	{
		return FUNCTION_FAIL_RETURN;
	}

	int id = driver->getID();
	auto ptr = reinterpret_cast<uintptr_t>(driver);
	IPC_RETURN(int id, uintptr_t ptr);
}

IPC_API(Player_IsInModShop, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
	if (data)
	{
		bool isIn = data->isInModShop();
		IPC_RETURN(bool isIn);
	}
	IPC_RETURN();
}

IPC_API(Player_GetSirenState, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
	IVehicle* vehicle = data->getVehicle();
	if (vehicle)
	{
		int state = vehicle->getSirenState();
		IPC_RETURN(int state);
	}
	IPC_RETURN();
}

IPC_API(Player_GetLandingGearState, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
	IVehicle* vehicle = data->getVehicle();
	if (vehicle)
	{
		int state = vehicle->getLandingGearState();
		IPC_RETURN(int state);
	}
	IPC_RETURN();
}

IPC_API(Player_GetHydraReactorAngle, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
	IVehicle* vehicle = data->getVehicle();
	if (vehicle)
	{
		float angle = vehicle->getHydraThrustAngle();
		IPC_RETURN(float angle);
	}
	IPC_RETURN();
}

IPC_API(Player_GetTrainSpeed, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(player_);
	IVehicle* vehicle = data->getVehicle();
	if (vehicle)
	{
		float speed = vehicle->getTrainSpeed();
		IPC_RETURN(float speed);
	}
	IPC_RETURN();
}

IPC_API(Vehicle_GetSirenState, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	int state = vehicle_->getSirenState();
	IPC_RETURN(int state);
}

IPC_API(Vehicle_GetHydraReactorAngle, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	float angle = vehicle_->getHydraThrustAngle();
	IPC_RETURN(float angle);
}

IPC_API(Vehicle_GetTrainSpeed, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	float speed = vehicle_->getTrainSpeed();
	IPC_RETURN(float speed);
}

IPC_API(Vehicle_GetMatrix, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	glm::mat3 mat = glm::transpose(glm::mat3_cast(vehicle_->getRotation().q));

	float rightX = mat[0][0];
	float rightY = mat[0][1];
	float rightZ = mat[0][2];
	float upX = mat[1][0];
	float upY = mat[1][1];
	float upZ = mat[1][2];
	float atX = mat[2][0];
	float atY = mat[2][1];
	float atZ = mat[2][2];
	IPC_RETURN(float rightX, float rightY, float rightZ, float upX, float upY, float upZ, float atX, float atY, float atZ);
}

IPC_API(Vehicle_GetOccupant, uintptr_t vehicle, int seat)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IPlayer* driver = vehicle_->getDriver();
	// Looking for driver
	if (seat == 0)
	{
		if (driver == nullptr) {
			return FUNCTION_FAIL_RETURN;
		}

		auto id = driver->getID();
		auto ptr = reinterpret_cast<uintptr_t>(driver);
		IPC_RETURN(int id, uintptr_t ptr);
	}
	// Looking for a passenger
	else
	{
		const FlatHashSet<IPlayer*>& passengers = vehicle_->getPassengers();
		for (auto& passenger : passengers)
		{
			if (passenger)
			{
				IPlayerVehicleData* data = queryExtension<IPlayerVehicleData>(passenger);
				if (data && data->getSeat() == seat)
				{
					auto id = passenger->getID();
					auto ptr = reinterpret_cast<uintptr_t>(passenger);
					IPC_RETURN(int id, uintptr_t ptr);
				}
			}
		}
	}
	return FUNCTION_FAIL_RETURN;
}

IPC_API(Vehicle_CountOccupants, uintptr_t vehicle)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->vehicles, IVehicle, vehicle, vehicle_);
	IPlayer* driver = vehicle_->getDriver();
	const FlatHashSet<IPlayer*>& passengers = vehicle_->getPassengers();
	int occupants = 0;

	if (driver)
	{
		occupants++;
	}
	occupants += passengers.size();

	IPC_RETURN(int occupants);
}
