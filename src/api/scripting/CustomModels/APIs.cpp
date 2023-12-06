#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

IPC_API(CustomModel_AddCharModel, int baseid, int newid, ConstStringRef dff, ConstStringRef textureLibrary)
{
	auto models = OmpManager::Get()->models;

	if (!models)
		IPC_RETURN();

	bool ret = models->addCustomModel(ModelType::Skin, newid, baseid, dff, textureLibrary);
	IPC_RETURN(bool ret);
}

IPC_API(CustomModel_AddSimpleModel, int virtualWorld, int baseid, int newid, ConstStringRef dff, ConstStringRef textureLibrary)
{
	auto models = OmpManager::Get()->models;

	if (!models)
		IPC_RETURN();

	bool ret = models->addCustomModel(ModelType::Object, newid, baseid, dff, textureLibrary, virtualWorld);
	IPC_RETURN(bool ret);
}

IPC_API(CustomModel_AddSimpleModelTimed, int virtualWorld, int baseid, int newid, ConstStringRef dff, ConstStringRef textureLibrary, int timeOn, int timeOff)
{
	auto models = OmpManager::Get()->models;

	if (!models)
		IPC_RETURN();

	bool ret = models->addCustomModel(ModelType::Object, newid, baseid, dff, textureLibrary, virtualWorld, timeOn, timeOff);
	IPC_RETURN(bool ret);
}

IPC_API(Player_GetCustomSkin, uintptr_t player)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCustomModelsData* data = queryExtension<IPlayerCustomModelsData>(player_);
	if (!data)
	{
		IPC_RETURN();
	}
	auto skin = data->getCustomSkin();
	IPC_RETURN(int skin);
}

IPC_API(CustomModel_RedirectDownload, uintptr_t player, ConstStringRef url)
{
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_);
	IPlayerCustomModelsData* data = queryExtension<IPlayerCustomModelsData>(player_);
	if (!data)
	{
		IPC_RETURN();
	}
	if (!data->sendDownloadUrl(url))
	{
		OmpManager::Get()->core->logLn(LogLevel::Warning, "This native can be used only within OnPlayerRequestDownload callback.");
		IPC_RETURN();
	}
	IPC_RETURN();
}

IPC_API(CustomModel_FindModelFileNameFromCRC, int crc)
{
	auto models = OmpManager::Get()->models;

	if (!models)
	{
		IPC_RETURN();
	}

	ConstStringRef output = models->getModelNameFromChecksum(crc);
	int len = std::get<StringView>(output).length();
	IPC_RETURN(ConstStringRef output, int len);
}

IPC_API(CustomModel_IsValid, int modelId)
{
	auto models = OmpManager::Get()->models;

	if (!models)
	{
		IPC_RETURN();
	}

	auto valid = models->isValidCustomModel(modelId);
	IPC_RETURN(bool valid);
}

IPC_API(CustomModel_GetPath, int modelId)
{
	auto models = OmpManager::Get()->models;

	if (!models)
	{
		IPC_RETURN();
	}

	StringView dffPathSV {};
	StringView txdPathSV {};

	auto status = models->getCustomModelPath(modelId, dffPathSV, txdPathSV);

	ConstStringRef dffPath = dffPathSV;
	ConstStringRef txdPath = txdPathSV;

	IPC_RETURN(bool status, ConstStringRef dffPath, ConstStringRef txdPath);
}
