#pragma once
#include <robin_hood.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>
#include "../utils/Singleton.hpp"
#include "../utils/MagicMacro.hpp"

class MessageSocket;

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
