#include "lua_bindings_channel.hpp"
#include "VCTChannel.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_channel_Channel_Request(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"VCT.Channel",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "VCT.Channel:Request");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "VCT.Channel:Request");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_channel_Channel_Request'", nullptr);
            return 0;
        }
        std::string ret = VCT::Channel::Request(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "VCT.Channel:Request");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "VCT.Channel:Request");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "VCT.Channel:Request");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_channel_Channel_Request'", nullptr);
            return 0;
        }
        std::string ret = VCT::Channel::Request(arg0, arg1, arg2);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::function<void (const std::basic_string<char> &)> arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "VCT.Channel:Request");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "VCT.Channel:Request");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "VCT.Channel:Request");
        int callback = toluafix_ref_function(tolua_S,5,0);
        do {
            auto lambda = [callback](const std::basic_string<char> & larg0) -> void {
                LuaStack *stack = LuaEngine::getInstance()->getLuaStack();
                stack->pushString(larg0);
                stack->executeFunctionByHandler(callback, 1);
                stack->clean();
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            arg3 = lambda;
			assert(false);
		} while(0)
		;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_channel_Channel_Request'", nullptr);
            return 0;
        }
        std::string ret = VCT::Channel::Request(arg0, arg1, arg2, arg3);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "VCT.Channel:Request",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_channel_Channel_Request'.",&tolua_err);
#endif
    return 0;
}
int lua_channel_Channel_Response(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"VCT.Channel",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "VCT.Channel:Response");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "VCT.Channel:Response");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_channel_Channel_Response'", nullptr);
            return 0;
        }
        VCT::Channel::Response(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "VCT.Channel:Response",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_channel_Channel_Response'.",&tolua_err);
#endif
    return 0;
}
static int lua_channel_Channel_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Channel)");
    return 0;
}

int lua_register_channel_Channel(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"VCT.Channel");
    tolua_cclass(tolua_S,"Channel","VCT.Channel","",nullptr);

    tolua_beginmodule(tolua_S,"Channel");
        tolua_function(tolua_S,"Request", lua_channel_Channel_Request);
        tolua_function(tolua_S,"Response", lua_channel_Channel_Response);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(VCT::Channel).name();
    g_luaType[typeName] = "VCT.Channel";
    g_typeCast["Channel"] = "VCT.Channel";
    return 1;
}
TOLUA_API int register_all_channel(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"VCT",0);
	tolua_beginmodule(tolua_S,"VCT");

	lua_register_channel_Channel(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

