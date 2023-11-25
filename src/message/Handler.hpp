#include <robin_hood.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>
#include "../utils/Singleton.hpp"

class MessageSocket;

#define RETURN_VALUE(x) returnValue(x)
#define RETURN_ERROR(x) returnError(x)
#define UNDEFINED_FAILED_RETURN(x) RETURN_ERROR("undefined error")
#define FUNCTION_FAIL_RETURN RETURN_ERROR(this->name_ + ": error while executing.")
#define NO_DATA_SUCCESS_RETURN RETURN_VALUE(true)

template<typename T>
inline nlohmann::json returnError(T value)
{
	nlohmann::json obj;
	obj["ret"]["error"] = value;
	obj["ret"]["value"] = nullptr;
	return obj;
}

template<typename T>
inline nlohmann::json returnValue(T value)
{
	nlohmann::json obj;
	obj["ret"]["error"] = nullptr;
	obj["ret"]["value"] = value;
	return obj;
}

class MessageHandler
{
public:
	std::string name_;

	MessageHandler()
	{}

	~MessageHandler()
	{}

	virtual nlohmann::json Call(const nlohmann::json& params, MessageSocket* messageSocket) = 0;
};

class MessageHandlerPool : public Singleton<MessageHandlerPool>
{
public:
	robin_hood::unordered_flat_map<std::string, MessageHandler*> handlers; // Fully initialized handlers with registered functions
	std::vector<MessageHandler*> handlerInstances; // To be fully initialized later

	nlohmann::json Call(const std::string& name, const nlohmann::json& params, MessageSocket* messageSocket)
	{
		auto it = handlers.find(name);
		if (it != handlers.end())
		{
			MessageHandler* handler = (*it).second;
			return handler->Call(params, messageSocket);
		}
		else
		{
			return RETURN_ERROR("handler_not_found");
		}
	}

	void Register(MessageHandler* messageHandler)
	{
		handlerInstances.push_back(messageHandler);
	}

	void UnRegister(MessageHandler* messageHandler)
	{
		handlers.erase(messageHandler->name_);
		auto instance = std::find(handlerInstances.begin(), handlerInstances.end(), messageHandler);
		if (instance != handlerInstances.end())
		{
			handlerInstances.erase(instance);
		}
	}

	void Init()
	{
		for (auto instance : handlerInstances)
		{
			auto it = handlers.find(instance->name_);
			if (it != handlers.end())
			{
				it->second = instance;
			}
			else
			{
				handlers.insert({ instance->name_, instance });
			}
		}
	}
};

// name: name for IPC event sent from clients (other languages)
// params: params in nlohmann::json object
#define IPC_API(name, params)                                                        \
	class MessageHandler_##name : public MessageHandler                              \
	{                                                                                \
	public:                                                                          \
		MessageHandler_##name() {                                                    \
			MessageHandler::name_ = #name;                                           \
			MessageHandlerPool::Get()->Register(this);                               \
		}                                                                            \
																					 \
		~MessageHandler_##name()                                                     \
		{                                                                            \
			MessageHandlerPool::Get()->UnRegister(this);                             \
		}                                                                            \
																					 \
		nlohmann::json Call(params, MessageSocket* messageSocket) override;          \
	};                                                                               \
																					 \
	MessageHandler_##name ipc_api_##name;                                            \
																					 \
	nlohmann::json MessageHandler_##name::Call(params, MessageSocket* messageSocket) \

// name: name for IPC event sent from clients (other languages)
// params: params in nlohmann::json object
// messageSocket: an instance of relevant messageSocket
#define IPC_API_EX(name, params, messageSocket)                                      \
	class MessageHandler_##name : public MessageHandler                              \
	{                                                                                \
	public:                                                                          \
		MessageHandler_##name() {                                                    \
			MessageHandler::name_ = #name;                                           \
			MessageHandlerPool::Get()->Register(this);                               \
		}                                                                            \
																					 \
		~MessageHandler_##name()                                                     \
		{                                                                            \
			MessageHandlerPool::Get()->UnRegister(this);                             \
		}                                                                            \
																					 \
		nlohmann::json Call(params, messageSocket) override;                         \
	};                                                                               \
																					 \
	MessageHandler_##name ipc_api_##name;                                            \
																					 \
	nlohmann::json MessageHandler_##name::Call(params, messageSocket)                \

