#include "../../../message/Handler.hpp"
#include "../Manager.hpp"

#define GET_VAR_COMP(comp)                           	\
	IVariablesComponent* comp = OmpManager::Get()->vars; \
	if (comp == nullptr)                                  \
		IPC_RETURN();

#define GET_PLAYER_VAR_COMP(comp)                                       		\
	GET_POOL_ENTITY_CHECKED(OmpManager::Get()->players, IPlayer, player, player_); \
	IPlayerVariableData* comp = queryExtension<IPlayerVariableData>(player_); 		\
	if (comp == nullptr)                                                     		\
		IPC_RETURN();

IPC_API(SVar_SetInt, ConstStringRef varname, int value)
{
	if (varname.empty())
	{
		IPC_RETURN();
	}

	GET_VAR_COMP(component);
	component->setInt(varname, value);
	IPC_RETURN();
}

IPC_API(SVar_GetInt, ConstStringRef varname)
{
	GET_VAR_COMP(component);
	auto value = component->getInt(varname);
	IPC_RETURN(int value);
}

IPC_API(SVar_SetString, ConstStringRef varname, ConstStringRef value)
{
	if (varname.empty())
	{
		IPC_RETURN();
	}

	GET_VAR_COMP(component);
	component->setString(varname, value);
	IPC_RETURN();
}

IPC_API(SVar_GetString, ConstStringRef varname)
{
	GET_VAR_COMP(component);
	// If string is empty, output will not be updated or set to anything and will remain with old data.
	StringView var = component->getString(varname);
	if (var.empty())
	{
		IPC_RETURN();
	}
	ConstStringRef output = var;
	int len = std::get<StringView>(output).length();
	IPC_RETURN(ConstStringRef output, int len);
}

IPC_API(SVar_SetFloat, ConstStringRef varname, float value)
{
	if (varname.empty())
	{
		IPC_RETURN();
	}

	GET_VAR_COMP(component);
	component->setFloat(varname, value);
	IPC_RETURN();
}

IPC_API(SVar_GetFloat, ConstStringRef varname)
{
	GET_VAR_COMP(component);
	auto value = component->getFloat(varname);
	IPC_RETURN(float value);
}

IPC_API(SVar_Delete, ConstStringRef varname)
{
	GET_VAR_COMP(component);
	auto ret = component->erase(varname);
	IPC_RETURN(bool ret);
}

IPC_API(SVar_GetUpperIndex)
{
	GET_VAR_COMP(component);
	auto size = component->size();
	IPC_RETURN(int size);
}

IPC_API(SVar_GetNameAtIndex, int index)
{
	GET_VAR_COMP(component);
	StringView varname;
	bool res = component->getKeyAtIndex(index, varname);
	ConstStringRef output;
	if (res)
	{
		output = varname;
	}
	IPC_RETURN(ConstStringRef output, bool res);
}

IPC_API(SVar_GetType, ConstStringRef varname)
{
	GET_VAR_COMP(component);
	int type = int(component->getType(varname));
	IPC_RETURN(int type);
}

/*
	Per-Player Variables
*/

IPC_API(PVar_SetInt, uintptr_t player, ConstStringRef varname, int value)
{
	GET_PLAYER_VAR_COMP(component);
	component->setInt(varname, value);
	IPC_RETURN();
}

IPC_API(PVar_GetInt, uintptr_t player, ConstStringRef varname)
{
	GET_PLAYER_VAR_COMP(component);
	auto value = component->getInt(varname);
	IPC_RETURN(int value);
}

IPC_API(PVar_SetString, uintptr_t player, ConstStringRef varname, ConstStringRef value)
{
	GET_PLAYER_VAR_COMP(component);
	component->setString(varname, value);
	IPC_RETURN();
}

IPC_API(PVar_GetString, uintptr_t player, ConstStringRef varname)
{
	GET_PLAYER_VAR_COMP(component);
	// If string is empty, output will not be updated or set to anything and will remain with old data.
	StringView var = component->getString(varname);
	if (var.empty())
	{
		IPC_RETURN();
	}
	ConstStringRef output = var;
	int len = std::get<StringView>(output).length();
	IPC_RETURN(ConstStringRef output, int len);
}

IPC_API(PVar_SetFloat, uintptr_t player, ConstStringRef varname, float value)
{
	GET_PLAYER_VAR_COMP(component);
	component->setFloat(varname, value);
	IPC_RETURN();
}

IPC_API(PVar_GetFloat, uintptr_t player, ConstStringRef varname)
{
	GET_PLAYER_VAR_COMP(component);
	auto value = component->getFloat(varname);
	IPC_RETURN(float value);
}

IPC_API(PVar_Delete, uintptr_t player, ConstStringRef varname)
{
	GET_PLAYER_VAR_COMP(component);
	auto ret = component->erase(varname);
	IPC_RETURN(bool ret);
}

IPC_API(PVar_GetUpperIndex, uintptr_t player)
{
	GET_PLAYER_VAR_COMP(component);
	auto size = component->size();
	IPC_RETURN(int size);
}

IPC_API(PVar_GetNameAtIndex, uintptr_t player, int index)
{
	GET_PLAYER_VAR_COMP(component);
	StringView varname;
	bool res = component->getKeyAtIndex(index, varname);
	ConstStringRef output;
	if (res)
	{
		output = varname;
	}
	IPC_RETURN(ConstStringRef output, bool res);
}

IPC_API(PVar_GetType, uintptr_t player, ConstStringRef varname)
{
	GET_PLAYER_VAR_COMP(component);
	int type = int(component->getType(varname));
	IPC_RETURN(int type);
}