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

#define LPAREN (
#define RPAREN )
#define COMMA ,

#define CAT(L, R) CAT_(L, R)
#define CAT_(L, R) L ## R
#define EXPAND(...) __VA_ARGS__

#define SPLIT(OP, D) EXPAND(OP CAT(SPLIT_, D) RPAREN)

#define SPLIT_int LPAREN int COMMA
#define SPLIT_char LPAREN char COMMA
#define SPLIT_float LPAREN float COMMA
#define SPLIT_double LPAREN double COMMA

#define DECLARE_VARIABLE_NATIVELY_(x, y) x y = params[#y];
#define DECLARE_VARIABLE_NATIVELY(A) SPLIT(DECLARE_VARIABLE_NATIVELY_, A)

#define CREATE_FUNCTION_SIG_ARG_(x, y) x y,
#define CREATE_FUNCTION_SIG_ARG(A) SPLIT(CREATE_FUNCTION_SIG_ARG_, A)

#define CREATE_FUNCTION_CALL_ARG_(x, y) y,
#define CREATE_FUNCTION_CALL_ARG(A) SPLIT(CREATE_FUNCTION_CALL_ARG_, A)

#ifdef _MSC_VER
#define OMP_IPC__NUM_ARGS(...) OMP_IPC__NUM_ARGS_(OMP_IPC__NUM_ARGS_MSVC(__VA_ARGS__))

#define OMP_IPC__NUM_ARGS_MSVC(...) unused, __VA_ARGS__
#define OMP_IPC__NUM_ARGS_(...) EXPAND(OMP_IPC__NUM_ARGS_IMPL(__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define OMP_IPC__NUM_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, N, ...) N
#else
#define OMP_IPC__NUM_ARGS(...) OMP_IPC__NUM_ARGS_(__VA_ARGS__)
#define OMP_IPC__NUM_ARGS_(...) OMP_IPC__NUM_ARGS_IMPL(0, ##__VA_ARGS__, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define OMP_IPC__NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, N, ...) N
#endif

#define CAT_VARIADIC(a, ...) CAT_VARIADIC_(a, __VA_ARGS__)
#define CAT_VARIADIC_(a, ...) a##__VA_ARGS__

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define EVAL(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__


// Prepend args for declaring variables
// DV = declare variables
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_0(a)
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_1(a) DECLARE_VARIABLE_NATIVELY(a)
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_2(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_1(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_3(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_2(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_4(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_3(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_5(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_4(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_6(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_5(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_7(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_6(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_8(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_7(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_9(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_8(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_10(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_9(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_11(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_10(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_12(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_11(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_13(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_12(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_14(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_13(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_15(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_14(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_16(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_15(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_17(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_16(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_18(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_17(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_19(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_18(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_20(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_19(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_21(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_20(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_22(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_21(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_23(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_22(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_24(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_23(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_25(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_24(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_26(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_25(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_27(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_26(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_28(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_27(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_29(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_28(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_30(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_29(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_31(a, ...) DECLARE_VARIABLE_NATIVELY(a) EVAL(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_30(__VA_ARGS__))
#define DV_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(...) CAT_VARIADIC(DV_PREPEND_EACH_ARG_WITH_HASH_ARG_, OMP_IPC__NUM_ARGS(__VA_ARGS__)) (__VA_ARGS__)

// Prepend args for function signature
// FS = function signature
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_0(a)
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_1(a) CREATE_FUNCTION_SIG_ARG(a)
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_2(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_1(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_3(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_2(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_4(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_3(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_5(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_4(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_6(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_5(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_7(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_6(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_8(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_7(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_9(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_8(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_10(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_9(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_11(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_10(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_12(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_11(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_13(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_12(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_14(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_13(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_15(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_14(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_16(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_15(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_17(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_16(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_18(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_17(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_19(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_18(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_20(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_19(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_21(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_20(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_22(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_21(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_23(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_22(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_24(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_23(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_25(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_24(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_26(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_25(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_27(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_26(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_28(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_27(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_29(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_28(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_30(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_29(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_31(a, ...) CREATE_FUNCTION_SIG_ARG(a) EVAL(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_30(__VA_ARGS__))
#define FS_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(...) CAT_VARIADIC(FS_PREPEND_EACH_ARG_WITH_HASH_ARG_, OMP_IPC__NUM_ARGS(__VA_ARGS__)) (__VA_ARGS__) 

// Prepend args for function call
// FC = function call
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_0(a)
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_1(a) CREATE_FUNCTION_CALL_ARG(a)
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_2(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_1(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_3(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_2(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_4(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_3(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_5(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_4(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_6(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_5(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_7(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_6(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_8(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_7(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_9(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_8(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_10(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_9(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_11(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_10(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_12(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_11(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_13(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_12(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_14(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_13(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_15(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_14(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_16(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_15(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_17(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_16(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_18(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_17(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_19(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_18(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_20(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_19(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_21(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_20(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_22(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_21(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_23(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_22(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_24(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_23(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_25(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_24(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_26(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_25(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_27(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_26(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_28(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_27(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_29(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_28(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_30(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_29(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_31(a, ...) CREATE_FUNCTION_CALL_ARG(a) EVAL(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_30(__VA_ARGS__))
#define FC_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(...) CAT_VARIADIC(FC_PREPEND_EACH_ARG_WITH_HASH_ARG_, OMP_IPC__NUM_ARGS(__VA_ARGS__)) (__VA_ARGS__) 

#define GENERATE_PARAMS_TO_DECLARE_VARS(...) DV_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(__VA_ARGS__)
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(...) FS_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(__VA_ARGS__)
#define GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(...) FC_PREPEND_EACH_ARG_WITH_HASH_ARG_IMPL(__VA_ARGS__)

// name: name for IPC event sent from clients (other languages)
// params: params in nlohmann::json object
#define IPC_API(name, ...)																											\
	class MessageHandler_##name : public MessageHandler																				\
	{																																\
	public:																															\
		MessageHandler_##name() {																									\
			MessageHandler::name_ = #name;																							\
			MessageHandlerPool::Get()->Register(this);																				\
		}																															\
																																	\
		~MessageHandler_##name()																									\
		{																															\
			MessageHandlerPool::Get()->UnRegister(this);																			\
		}																															\
																																	\
		nlohmann::json Call(const nlohmann::json& params, MessageSocket* messageSocket) override									\
		{																															\
			GENERATE_PARAMS_TO_DECLARE_VARS(__VA_ARGS__)																			\
			return Call(GENERATE_PARAMS_TO_USE_IN_FUNCTION_CALL(__VA_ARGS__) messageSocket);										\
		}																															\
		nlohmann::json Call(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) MessageSocket* messageSocket);						\
	};																																\
																																	\
	MessageHandler_##name ipc_api_##name;																							\
																																	\
	nlohmann::json MessageHandler_##name::Call(GENERATE_PARAMS_TO_USE_IN_FUNCTION_SIG(__VA_ARGS__) MessageSocket* messageSocket)	\

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

