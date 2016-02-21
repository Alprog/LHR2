#include "lua_cocos2dx_experimental_auto.hpp"
#include "CCFastTMXLayer.h"
#include "CCFastTMXTiledMap.h"
#include "CCFrameBuffer.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_experimental_TMXLayer_getPositionAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getPositionAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccexp.TMXLayer:getPositionAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getPositionAt'", nullptr);
            return 0;
        }
        cocos2d::Vec2 ret = cobj->getPositionAt(arg0);
        vec2_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getPositionAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getPositionAt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setLayerOrientation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setLayerOrientation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.TMXLayer:setLayerOrientation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setLayerOrientation'", nullptr);
            return 0;
        }
        cobj->setLayerOrientation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setLayerOrientation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setLayerOrientation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getLayerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getLayerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getLayerSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getLayerSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getLayerSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getLayerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setMapTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setMapTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccexp.TMXLayer:setMapTileSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setMapTileSize'", nullptr);
            return 0;
        }
        cobj->setMapTileSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setMapTileSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setMapTileSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getLayerOrientation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getLayerOrientation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getLayerOrientation'", nullptr);
            return 0;
        }
        int ret = cobj->getLayerOrientation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getLayerOrientation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getLayerOrientation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "ccexp.TMXLayer:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setProperties",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setProperties'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setLayerName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setLayerName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXLayer:setLayerName");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setLayerName'", nullptr);
            return 0;
        }
        cobj->setLayerName(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setLayerName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setLayerName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_removeTileAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_removeTileAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccexp.TMXLayer:removeTileAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_removeTileAt'", nullptr);
            return 0;
        }
        cobj->removeTileAt(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:removeTileAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_removeTileAt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getProperties'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::ValueMap& ret = cobj->getProperties();
            ccvaluemap_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccexp.TMXLayer:getProperties",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getProperties'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setupTiles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setupTiles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setupTiles'", nullptr);
            return 0;
        }
        cobj->setupTiles();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setupTiles",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setupTiles'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setupTileSprite(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setupTileSprite'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocos2d::Sprite* arg0;
        cocos2d::Vec2 arg1;
        int arg2;

        ok &= luaval_to_object<cocos2d::Sprite>(tolua_S, 2, "cc.Sprite",&arg0, "ccexp.TMXLayer:setupTileSprite");

        ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccexp.TMXLayer:setupTileSprite");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.TMXLayer:setupTileSprite");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setupTileSprite'", nullptr);
            return 0;
        }
        cobj->setupTileSprite(arg0, arg1, arg2);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setupTileSprite",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setupTileSprite'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setTileGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setTileGID'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.TMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccexp.TMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::TMXTileFlags_ arg2;
            ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.TMXLayer:setTileGID");

            if (!ok) { break; }
            cobj->setTileGID(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.TMXLayer:setTileGID");

            if (!ok) { break; }
            cocos2d::Vec2 arg1;
            ok &= luaval_to_vec2(tolua_S, 3, &arg1, "ccexp.TMXLayer:setTileGID");

            if (!ok) { break; }
            cobj->setTileGID(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccexp.TMXLayer:setTileGID",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setTileGID'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getMapTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getMapTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getMapTileSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getMapTileSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getMapTileSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getMapTileSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXLayer:getProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getProperty'", nullptr);
            return 0;
        }
        cocos2d::Value ret = cobj->getProperty(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getProperty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getProperty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setLayerSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setLayerSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccexp.TMXLayer:setLayerSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setLayerSize'", nullptr);
            return 0;
        }
        cobj->setLayerSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setLayerSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setLayerSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getLayerName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getLayerName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getLayerName'", nullptr);
            return 0;
        }
        const std::string& ret = cobj->getLayerName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getLayerName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getLayerName'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_setTileSet(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_setTileSet'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::TMXTilesetInfo* arg0;

        ok &= luaval_to_object<cocos2d::TMXTilesetInfo>(tolua_S, 2, "cc.TMXTilesetInfo",&arg0, "ccexp.TMXLayer:setTileSet");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_setTileSet'", nullptr);
            return 0;
        }
        cobj->setTileSet(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:setTileSet",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_setTileSet'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getTileSet(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getTileSet'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getTileSet'", nullptr);
            return 0;
        }
        cocos2d::TMXTilesetInfo* ret = cobj->getTileSet();
        object_to_luaval<cocos2d::TMXTilesetInfo>(tolua_S, "cc.TMXTilesetInfo",(cocos2d::TMXTilesetInfo*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getTileSet",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getTileSet'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_getTileAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXLayer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXLayer_getTileAt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vec2 arg0;

        ok &= luaval_to_vec2(tolua_S, 2, &arg0, "ccexp.TMXLayer:getTileAt");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_getTileAt'", nullptr);
            return 0;
        }
        cocos2d::Sprite* ret = cobj->getTileAt(arg0);
        object_to_luaval<cocos2d::Sprite>(tolua_S, "cc.Sprite",(cocos2d::Sprite*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:getTileAt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_getTileAt'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.TMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        cocos2d::TMXTilesetInfo* arg0;
        cocos2d::TMXLayerInfo* arg1;
        cocos2d::TMXMapInfo* arg2;
        ok &= luaval_to_object<cocos2d::TMXTilesetInfo>(tolua_S, 2, "cc.TMXTilesetInfo",&arg0, "ccexp.TMXLayer:create");
        ok &= luaval_to_object<cocos2d::TMXLayerInfo>(tolua_S, 3, "cc.TMXLayerInfo",&arg1, "ccexp.TMXLayer:create");
        ok &= luaval_to_object<cocos2d::TMXMapInfo>(tolua_S, 4, "cc.TMXMapInfo",&arg2, "ccexp.TMXLayer:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::TMXLayer* ret = cocos2d::experimental::TMXLayer::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::experimental::TMXLayer>(tolua_S, "ccexp.TMXLayer",(cocos2d::experimental::TMXLayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.TMXLayer:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_TMXLayer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXLayer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXLayer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::TMXLayer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.TMXLayer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXLayer:TMXLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXLayer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_TMXLayer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TMXLayer)");
    return 0;
}

int lua_register_cocos2dx_experimental_TMXLayer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.TMXLayer");
    tolua_cclass(tolua_S,"TMXLayer","ccexp.TMXLayer","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"TMXLayer");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_TMXLayer_constructor);
        tolua_function(tolua_S,"getPositionAt",lua_cocos2dx_experimental_TMXLayer_getPositionAt);
        tolua_function(tolua_S,"setLayerOrientation",lua_cocos2dx_experimental_TMXLayer_setLayerOrientation);
        tolua_function(tolua_S,"getLayerSize",lua_cocos2dx_experimental_TMXLayer_getLayerSize);
        tolua_function(tolua_S,"setMapTileSize",lua_cocos2dx_experimental_TMXLayer_setMapTileSize);
        tolua_function(tolua_S,"getLayerOrientation",lua_cocos2dx_experimental_TMXLayer_getLayerOrientation);
        tolua_function(tolua_S,"setProperties",lua_cocos2dx_experimental_TMXLayer_setProperties);
        tolua_function(tolua_S,"setLayerName",lua_cocos2dx_experimental_TMXLayer_setLayerName);
        tolua_function(tolua_S,"removeTileAt",lua_cocos2dx_experimental_TMXLayer_removeTileAt);
        tolua_function(tolua_S,"getProperties",lua_cocos2dx_experimental_TMXLayer_getProperties);
        tolua_function(tolua_S,"setupTiles",lua_cocos2dx_experimental_TMXLayer_setupTiles);
        tolua_function(tolua_S,"setupTileSprite",lua_cocos2dx_experimental_TMXLayer_setupTileSprite);
        tolua_function(tolua_S,"setTileGID",lua_cocos2dx_experimental_TMXLayer_setTileGID);
        tolua_function(tolua_S,"getMapTileSize",lua_cocos2dx_experimental_TMXLayer_getMapTileSize);
        tolua_function(tolua_S,"getProperty",lua_cocos2dx_experimental_TMXLayer_getProperty);
        tolua_function(tolua_S,"setLayerSize",lua_cocos2dx_experimental_TMXLayer_setLayerSize);
        tolua_function(tolua_S,"getLayerName",lua_cocos2dx_experimental_TMXLayer_getLayerName);
        tolua_function(tolua_S,"setTileSet",lua_cocos2dx_experimental_TMXLayer_setTileSet);
        tolua_function(tolua_S,"getTileSet",lua_cocos2dx_experimental_TMXLayer_getTileSet);
        tolua_function(tolua_S,"getTileAt",lua_cocos2dx_experimental_TMXLayer_getTileAt);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_TMXLayer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::TMXLayer).name();
    g_luaType[typeName] = "ccexp.TMXLayer";
    g_typeCast["TMXLayer"] = "ccexp.TMXLayer";
    return 1;
}

int lua_cocos2dx_experimental_TMXTiledMap_setObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_setObjectGroups'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<cocos2d::TMXObjectGroup *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0, "ccexp.TMXTiledMap:setObjectGroups");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_setObjectGroups'", nullptr);
            return 0;
        }
        cobj->setObjectGroups(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:setObjectGroups",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_setObjectGroups'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getProperty(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperty'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXTiledMap:getProperty");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperty'", nullptr);
            return 0;
        }
        cocos2d::Value ret = cobj->getProperty(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getProperty",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperty'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_setMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccexp.TMXTiledMap:setMapSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapSize'", nullptr);
            return 0;
        }
        cobj->setMapSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:setMapSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getObjectGroup(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getObjectGroup'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXTiledMap:getObjectGroup");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getObjectGroup'", nullptr);
            return 0;
        }
        cocos2d::TMXObjectGroup* ret = cobj->getObjectGroup(arg0);
        object_to_luaval<cocos2d::TMXObjectGroup>(tolua_S, "cc.TMXObjectGroup",(cocos2d::TMXObjectGroup*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getObjectGroup",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getObjectGroup'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getObjectGroups(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getObjectGroups'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            const cocos2d::Vector<cocos2d::TMXObjectGroup *>& ret = cobj->getObjectGroups();
            ccvector_to_luaval(tolua_S, ret);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "ccexp.TMXTiledMap:getObjectGroups",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getObjectGroups'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getTileSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getTileSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getTileSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getTileSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getMapSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapSize'", nullptr);
            return 0;
        }
        const cocos2d::Size& ret = cobj->getMapSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getMapSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperties'", nullptr);
            return 0;
        }
        const cocos2d::ValueMap& ret = cobj->getProperties();
        ccvaluemap_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getProperties",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getProperties'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getPropertiesForGID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getPropertiesForGID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.TMXTiledMap:getPropertiesForGID");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getPropertiesForGID'", nullptr);
            return 0;
        }
        cocos2d::Value ret = cobj->getPropertiesForGID(arg0);
        ccvalue_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getPropertiesForGID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getPropertiesForGID'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_setTileSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_setTileSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Size arg0;

        ok &= luaval_to_size(tolua_S, 2, &arg0, "ccexp.TMXTiledMap:setTileSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_setTileSize'", nullptr);
            return 0;
        }
        cobj->setTileSize(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:setTileSize",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_setTileSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_setProperties(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_setProperties'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::ValueMap arg0;

        ok &= luaval_to_ccvaluemap(tolua_S, 2, &arg0, "ccexp.TMXTiledMap:setProperties");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_setProperties'", nullptr);
            return 0;
        }
        cobj->setProperties(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:setProperties",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_setProperties'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getLayer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXTiledMap:getLayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getLayer'", nullptr);
            return 0;
        }
        cocos2d::experimental::TMXLayer* ret = cobj->getLayer(arg0);
        object_to_luaval<cocos2d::experimental::TMXLayer>(tolua_S, "ccexp.TMXLayer",(cocos2d::experimental::TMXLayer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_getMapOrientation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapOrientation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapOrientation'", nullptr);
            return 0;
        }
        int ret = cobj->getMapOrientation();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:getMapOrientation",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_getMapOrientation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_setMapOrientation(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::TMXTiledMap* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::TMXTiledMap*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapOrientation'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.TMXTiledMap:setMapOrientation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapOrientation'", nullptr);
            return 0;
        }
        cobj->setMapOrientation(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.TMXTiledMap:setMapOrientation",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_setMapOrientation'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXTiledMap:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::TMXTiledMap* ret = cocos2d::experimental::TMXTiledMap::create(arg0);
        object_to_luaval<cocos2d::experimental::TMXTiledMap>(tolua_S, "ccexp.TMXTiledMap",(cocos2d::experimental::TMXTiledMap*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.TMXTiledMap:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_TMXTiledMap_createWithXML(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.TMXTiledMap",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.TMXTiledMap:createWithXML");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "ccexp.TMXTiledMap:createWithXML");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_TMXTiledMap_createWithXML'", nullptr);
            return 0;
        }
        cocos2d::experimental::TMXTiledMap* ret = cocos2d::experimental::TMXTiledMap::createWithXML(arg0, arg1);
        object_to_luaval<cocos2d::experimental::TMXTiledMap>(tolua_S, "ccexp.TMXTiledMap",(cocos2d::experimental::TMXTiledMap*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.TMXTiledMap:createWithXML",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_TMXTiledMap_createWithXML'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_experimental_TMXTiledMap_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TMXTiledMap)");
    return 0;
}

int lua_register_cocos2dx_experimental_TMXTiledMap(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.TMXTiledMap");
    tolua_cclass(tolua_S,"TMXTiledMap","ccexp.TMXTiledMap","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"TMXTiledMap");
        tolua_function(tolua_S,"setObjectGroups",lua_cocos2dx_experimental_TMXTiledMap_setObjectGroups);
        tolua_function(tolua_S,"getProperty",lua_cocos2dx_experimental_TMXTiledMap_getProperty);
        tolua_function(tolua_S,"setMapSize",lua_cocos2dx_experimental_TMXTiledMap_setMapSize);
        tolua_function(tolua_S,"getObjectGroup",lua_cocos2dx_experimental_TMXTiledMap_getObjectGroup);
        tolua_function(tolua_S,"getObjectGroups",lua_cocos2dx_experimental_TMXTiledMap_getObjectGroups);
        tolua_function(tolua_S,"getTileSize",lua_cocos2dx_experimental_TMXTiledMap_getTileSize);
        tolua_function(tolua_S,"getMapSize",lua_cocos2dx_experimental_TMXTiledMap_getMapSize);
        tolua_function(tolua_S,"getProperties",lua_cocos2dx_experimental_TMXTiledMap_getProperties);
        tolua_function(tolua_S,"getPropertiesForGID",lua_cocos2dx_experimental_TMXTiledMap_getPropertiesForGID);
        tolua_function(tolua_S,"setTileSize",lua_cocos2dx_experimental_TMXTiledMap_setTileSize);
        tolua_function(tolua_S,"setProperties",lua_cocos2dx_experimental_TMXTiledMap_setProperties);
        tolua_function(tolua_S,"getLayer",lua_cocos2dx_experimental_TMXTiledMap_getLayer);
        tolua_function(tolua_S,"getMapOrientation",lua_cocos2dx_experimental_TMXTiledMap_getMapOrientation);
        tolua_function(tolua_S,"setMapOrientation",lua_cocos2dx_experimental_TMXTiledMap_setMapOrientation);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_TMXTiledMap_create);
        tolua_function(tolua_S,"createWithXML", lua_cocos2dx_experimental_TMXTiledMap_createWithXML);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::TMXTiledMap).name();
    g_luaType[typeName] = "ccexp.TMXTiledMap";
    g_typeCast["TMXTiledMap"] = "ccexp.TMXTiledMap";
    return 1;
}

int lua_cocos2dx_experimental_RenderTarget_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTarget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTarget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTarget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTarget_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        unsigned int arg0;
        unsigned int arg1;
        cocos2d::Texture2D::PixelFormat arg2;
        int arg3;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTarget:init");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTarget:init");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTarget:init");

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccexp.RenderTarget:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTarget:init",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTarget_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTarget_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTarget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTarget",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTarget*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTarget_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_getTexture'", nullptr);
            return 0;
        }
        cocos2d::Texture2D* ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTarget:getTexture",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTarget_getTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTarget_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.RenderTarget",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTarget:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTarget:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTarget* ret = cocos2d::experimental::RenderTarget::create(arg0, arg1);
        object_to_luaval<cocos2d::experimental::RenderTarget>(tolua_S, "ccexp.RenderTarget",(cocos2d::experimental::RenderTarget*)ret);
        return 1;
    }
    if (argc == 3)
    {
        unsigned int arg0;
        unsigned int arg1;
        cocos2d::Texture2D::PixelFormat arg2;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTarget:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTarget:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTarget:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTarget* ret = cocos2d::experimental::RenderTarget::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::experimental::RenderTarget>(tolua_S, "ccexp.RenderTarget",(cocos2d::experimental::RenderTarget*)ret);
        return 1;
    }
    if (argc == 4)
    {
        unsigned int arg0;
        unsigned int arg1;
        cocos2d::Texture2D::PixelFormat arg2;
        int arg3;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTarget:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTarget:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTarget:create");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "ccexp.RenderTarget:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTarget* ret = cocos2d::experimental::RenderTarget::create(arg0, arg1, arg2, arg3);
        object_to_luaval<cocos2d::experimental::RenderTarget>(tolua_S, "ccexp.RenderTarget",(cocos2d::experimental::RenderTarget*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.RenderTarget:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTarget_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_RenderTarget_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTarget* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTarget_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::RenderTarget();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.RenderTarget");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTarget:RenderTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTarget_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_RenderTarget_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RenderTarget)");
    return 0;
}

int lua_register_cocos2dx_experimental_RenderTarget(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.RenderTarget");
    tolua_cclass(tolua_S,"RenderTarget","ccexp.RenderTarget","ccexp.RenderTargetBase",nullptr);

    tolua_beginmodule(tolua_S,"RenderTarget");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_RenderTarget_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_experimental_RenderTarget_init);
        tolua_function(tolua_S,"getTexture",lua_cocos2dx_experimental_RenderTarget_getTexture);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_RenderTarget_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::RenderTarget).name();
    g_luaType[typeName] = "ccexp.RenderTarget";
    g_typeCast["RenderTarget"] = "ccexp.RenderTarget";
    return 1;
}

int lua_cocos2dx_experimental_RenderTargetRenderBuffer_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetRenderBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTargetRenderBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTargetRenderBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        unsigned int arg0;
        unsigned int arg1;
        int arg2;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetRenderBuffer:init");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetRenderBuffer:init");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTargetRenderBuffer:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetRenderBuffer:init",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTargetRenderBuffer_getBuffer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetRenderBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTargetRenderBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTargetRenderBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_getBuffer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_getBuffer'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getBuffer();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetRenderBuffer:getBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_getBuffer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTargetRenderBuffer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.RenderTargetRenderBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetRenderBuffer:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetRenderBuffer:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetRenderBuffer* ret = cocos2d::experimental::RenderTargetRenderBuffer::create(arg0, arg1);
        object_to_luaval<cocos2d::experimental::RenderTargetRenderBuffer>(tolua_S, "ccexp.RenderTargetRenderBuffer",(cocos2d::experimental::RenderTargetRenderBuffer*)ret);
        return 1;
    }
    if (argc == 3)
    {
        unsigned int arg0;
        unsigned int arg1;
        int arg2;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetRenderBuffer:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetRenderBuffer:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTargetRenderBuffer:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetRenderBuffer* ret = cocos2d::experimental::RenderTargetRenderBuffer::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::experimental::RenderTargetRenderBuffer>(tolua_S, "ccexp.RenderTargetRenderBuffer",(cocos2d::experimental::RenderTargetRenderBuffer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.RenderTargetRenderBuffer:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_RenderTargetRenderBuffer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetRenderBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::RenderTargetRenderBuffer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.RenderTargetRenderBuffer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetRenderBuffer:RenderTargetRenderBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetRenderBuffer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_RenderTargetRenderBuffer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RenderTargetRenderBuffer)");
    return 0;
}

int lua_register_cocos2dx_experimental_RenderTargetRenderBuffer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.RenderTargetRenderBuffer");
    tolua_cclass(tolua_S,"RenderTargetRenderBuffer","ccexp.RenderTargetRenderBuffer","ccexp.RenderTargetBase",nullptr);

    tolua_beginmodule(tolua_S,"RenderTargetRenderBuffer");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_RenderTargetRenderBuffer_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_experimental_RenderTargetRenderBuffer_init);
        tolua_function(tolua_S,"getBuffer",lua_cocos2dx_experimental_RenderTargetRenderBuffer_getBuffer);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_RenderTargetRenderBuffer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::RenderTargetRenderBuffer).name();
    g_luaType[typeName] = "ccexp.RenderTargetRenderBuffer";
    g_typeCast["RenderTargetRenderBuffer"] = "ccexp.RenderTargetRenderBuffer";
    return 1;
}

int lua_cocos2dx_experimental_RenderTargetDepthStencil_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetDepthStencil* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTargetDepthStencil",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTargetDepthStencil*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        unsigned int arg0;
        unsigned int arg1;
        int arg2;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetDepthStencil:init");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetDepthStencil:init");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTargetDepthStencil:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetDepthStencil:init",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTargetDepthStencil_getBuffer(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetDepthStencil* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.RenderTargetDepthStencil",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::RenderTargetDepthStencil*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_getBuffer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_getBuffer'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getBuffer();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetDepthStencil:getBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_getBuffer'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_RenderTargetDepthStencil_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.RenderTargetDepthStencil",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        unsigned int arg0;
        unsigned int arg1;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetDepthStencil:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetDepthStencil:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetDepthStencil* ret = cocos2d::experimental::RenderTargetDepthStencil::create(arg0, arg1);
        object_to_luaval<cocos2d::experimental::RenderTargetDepthStencil>(tolua_S, "ccexp.RenderTargetDepthStencil",(cocos2d::experimental::RenderTargetDepthStencil*)ret);
        return 1;
    }
    if (argc == 3)
    {
        unsigned int arg0;
        unsigned int arg1;
        int arg2;
        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "ccexp.RenderTargetDepthStencil:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.RenderTargetDepthStencil:create");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "ccexp.RenderTargetDepthStencil:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetDepthStencil* ret = cocos2d::experimental::RenderTargetDepthStencil::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::experimental::RenderTargetDepthStencil>(tolua_S, "ccexp.RenderTargetDepthStencil",(cocos2d::experimental::RenderTargetDepthStencil*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.RenderTargetDepthStencil:create",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_RenderTargetDepthStencil_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::RenderTargetDepthStencil* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::RenderTargetDepthStencil();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.RenderTargetDepthStencil");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.RenderTargetDepthStencil:RenderTargetDepthStencil",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_RenderTargetDepthStencil_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_RenderTargetDepthStencil_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (RenderTargetDepthStencil)");
    return 0;
}

int lua_register_cocos2dx_experimental_RenderTargetDepthStencil(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.RenderTargetDepthStencil");
    tolua_cclass(tolua_S,"RenderTargetDepthStencil","ccexp.RenderTargetDepthStencil","ccexp.RenderTargetBase",nullptr);

    tolua_beginmodule(tolua_S,"RenderTargetDepthStencil");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_RenderTargetDepthStencil_constructor);
        tolua_function(tolua_S,"init",lua_cocos2dx_experimental_RenderTargetDepthStencil_init);
        tolua_function(tolua_S,"getBuffer",lua_cocos2dx_experimental_RenderTargetDepthStencil_getBuffer);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_RenderTargetDepthStencil_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::RenderTargetDepthStencil).name();
    g_luaType[typeName] = "ccexp.RenderTargetDepthStencil";
    g_typeCast["RenderTargetDepthStencil"] = "ccexp.RenderTargetDepthStencil";
    return 1;
}

int lua_cocos2dx_experimental_FrameBuffer_getFID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getFID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getFID'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getFID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getFID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getFID'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getTexel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getTexel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.FrameBuffer:getTexel");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccexp.FrameBuffer:getTexel");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getTexel'", nullptr);
            return 0;
        }
        cocos2d::Vec4 ret = cobj->getTexel(arg0, arg1);
        vec4_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getTexel",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getTexel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getWidth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getWidth'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getWidth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getWidth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_initWithGLView(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_initWithGLView'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::GLView* arg0;

        ok &= luaval_to_object<cocos2d::GLView>(tolua_S, 2, "cc.GLView",&arg0, "ccexp.FrameBuffer:initWithGLView");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_initWithGLView'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithGLView(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:initWithGLView",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_initWithGLView'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getDepthStencilTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getDepthStencilTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getDepthStencilTarget'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetDepthStencil* ret = cobj->getDepthStencilTarget();
        object_to_luaval<cocos2d::experimental::RenderTargetDepthStencil>(tolua_S, "ccexp.RenderTargetDepthStencil",(cocos2d::experimental::RenderTargetDepthStencil*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getDepthStencilTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getDepthStencilTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getClearDepth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getClearDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getClearDepth'", nullptr);
            return 0;
        }
        double ret = cobj->getClearDepth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getClearDepth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getClearDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getClearStencil(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getClearStencil'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getClearStencil'", nullptr);
            return 0;
        }
        int32_t ret = cobj->getClearStencil();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getClearStencil",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getClearStencil'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_applyFBO(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_applyFBO'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_applyFBO'", nullptr);
            return 0;
        }
        cobj->applyFBO();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:applyFBO",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_applyFBO'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_setClearStencil(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_setClearStencil'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int32_t arg0;

        ok &= luaval_to_int32(tolua_S, 2,&arg0, "ccexp.FrameBuffer:setClearStencil");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_setClearStencil'", nullptr);
            return 0;
        }
        cobj->setClearStencil(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:setClearStencil",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_setClearStencil'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getRenderTarget'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetBase* ret = cobj->getRenderTarget();
        object_to_luaval<cocos2d::experimental::RenderTargetBase>(tolua_S, "ccexp.RenderTargetBase",(cocos2d::experimental::RenderTargetBase*)ret);
        return 1;
    }
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.FrameBuffer:getRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getRenderTarget'", nullptr);
            return 0;
        }
        cocos2d::experimental::RenderTargetBase* ret = cobj->getRenderTarget(arg0);
        object_to_luaval<cocos2d::experimental::RenderTargetBase>(tolua_S, "ccexp.RenderTargetBase",(cocos2d::experimental::RenderTargetBase*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getRenderTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getRenderTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getHeight(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getHeight'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_clearFBO(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_clearFBO'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_clearFBO'", nullptr);
            return 0;
        }
        cobj->clearFBO();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:clearFBO",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_clearFBO'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_init(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        uint16_t arg0;
        unsigned int arg1;
        unsigned int arg2;

        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccexp.FrameBuffer:init");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.FrameBuffer:init");

        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccexp.FrameBuffer:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:init",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_isDefaultFBO(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_isDefaultFBO'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_isDefaultFBO'", nullptr);
            return 0;
        }
        bool ret = cobj->isDefaultFBO();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:isDefaultFBO",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_isDefaultFBO'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_setClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_setClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Color4F arg0;

        ok &=luaval_to_color4f(tolua_S, 2, &arg0, "ccexp.FrameBuffer:setClearColor");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_setClearColor'", nullptr);
            return 0;
        }
        cobj->setClearColor(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:setClearColor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_setClearColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getFBO(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getFBO'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getFBO'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->getFBO();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getFBO",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getFBO'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getClearColor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_getClearColor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getClearColor'", nullptr);
            return 0;
        }
        const cocos2d::Color4F& ret = cobj->getClearColor();
        color4f_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:getClearColor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getClearColor'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_attachRenderTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_attachRenderTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::experimental::RenderTargetBase* arg0;
        int arg1;

        ok &= luaval_to_object<cocos2d::experimental::RenderTargetBase>(tolua_S, 2, "ccexp.RenderTargetBase",&arg0, "ccexp.FrameBuffer:attachRenderTarget");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccexp.FrameBuffer:attachRenderTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_attachRenderTarget'", nullptr);
            return 0;
        }
        cobj->attachRenderTarget(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:attachRenderTarget",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_attachRenderTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_attachDepthStencilTarget(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_attachDepthStencilTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::experimental::RenderTargetDepthStencil* arg0;

        ok &= luaval_to_object<cocos2d::experimental::RenderTargetDepthStencil>(tolua_S, 2, "ccexp.RenderTargetDepthStencil",&arg0, "ccexp.FrameBuffer:attachDepthStencilTarget");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_attachDepthStencilTarget'", nullptr);
            return 0;
        }
        cobj->attachDepthStencilTarget(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:attachDepthStencilTarget",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_attachDepthStencilTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_newImage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_newImage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccexp.FrameBuffer:newImage");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_newImage'", nullptr);
            return 0;
        }
        cocos2d::Image* ret = cobj->newImage(arg0);
        object_to_luaval<cocos2d::Image>(tolua_S, "cc.Image",(cocos2d::Image*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:newImage",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_newImage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_setClearDepth(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_setClearDepth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "ccexp.FrameBuffer:setClearDepth");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_setClearDepth'", nullptr);
            return 0;
        }
        cobj->setClearDepth(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:setClearDepth",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_setClearDepth'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_setSize(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::experimental::FrameBuffer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FrameBuffer_setSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.FrameBuffer:setSize");

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "ccexp.FrameBuffer:setSize");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_setSize'", nullptr);
            return 0;
        }
        cobj->setSize(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:setSize",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_setSize'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getOrCreateDefaultFBO(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        cocos2d::GLView* arg0;
        ok &= luaval_to_object<cocos2d::GLView>(tolua_S, 2, "cc.GLView",&arg0, "ccexp.FrameBuffer:getOrCreateDefaultFBO");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getOrCreateDefaultFBO'", nullptr);
            return 0;
        }
        cocos2d::experimental::FrameBuffer* ret = cocos2d::experimental::FrameBuffer::getOrCreateDefaultFBO(arg0);
        object_to_luaval<cocos2d::experimental::FrameBuffer>(tolua_S, "ccexp.FrameBuffer",(cocos2d::experimental::FrameBuffer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.FrameBuffer:getOrCreateDefaultFBO",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getOrCreateDefaultFBO'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        uint16_t arg0;
        unsigned int arg1;
        unsigned int arg2;
        ok &= luaval_to_uint16(tolua_S, 2,&arg0, "ccexp.FrameBuffer:create");
        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ccexp.FrameBuffer:create");
        ok &= luaval_to_uint32(tolua_S, 4,&arg2, "ccexp.FrameBuffer:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_create'", nullptr);
            return 0;
        }
        cocos2d::experimental::FrameBuffer* ret = cocos2d::experimental::FrameBuffer::create(arg0, arg1, arg2);
        object_to_luaval<cocos2d::experimental::FrameBuffer>(tolua_S, "ccexp.FrameBuffer",(cocos2d::experimental::FrameBuffer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.FrameBuffer:create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_create'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_applyDefaultFBO(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_applyDefaultFBO'", nullptr);
            return 0;
        }
        cocos2d::experimental::FrameBuffer::applyDefaultFBO();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.FrameBuffer:applyDefaultFBO",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_applyDefaultFBO'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_clearAllFBOs(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_clearAllFBOs'", nullptr);
            return 0;
        }
        cocos2d::experimental::FrameBuffer::clearAllFBOs();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.FrameBuffer:clearAllFBOs",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_clearAllFBOs'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_getDefaultFBO(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.FrameBuffer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_getDefaultFBO'", nullptr);
            return 0;
        }
        cocos2d::experimental::FrameBuffer* ret = cocos2d::experimental::FrameBuffer::getDefaultFBO();
        object_to_luaval<cocos2d::experimental::FrameBuffer>(tolua_S, "ccexp.FrameBuffer",(cocos2d::experimental::FrameBuffer*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.FrameBuffer:getDefaultFBO",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_getDefaultFBO'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_experimental_FrameBuffer_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FrameBuffer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_experimental_FrameBuffer_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::FrameBuffer();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"ccexp.FrameBuffer");
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.FrameBuffer:FrameBuffer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FrameBuffer_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_experimental_FrameBuffer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FrameBuffer)");
    return 0;
}

int lua_register_cocos2dx_experimental_FrameBuffer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.FrameBuffer");
    tolua_cclass(tolua_S,"FrameBuffer","ccexp.FrameBuffer","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"FrameBuffer");
        tolua_function(tolua_S,"new",lua_cocos2dx_experimental_FrameBuffer_constructor);
        tolua_function(tolua_S,"getFID",lua_cocos2dx_experimental_FrameBuffer_getFID);
        tolua_function(tolua_S,"getTexel",lua_cocos2dx_experimental_FrameBuffer_getTexel);
        tolua_function(tolua_S,"getWidth",lua_cocos2dx_experimental_FrameBuffer_getWidth);
        tolua_function(tolua_S,"initWithGLView",lua_cocos2dx_experimental_FrameBuffer_initWithGLView);
        tolua_function(tolua_S,"getDepthStencilTarget",lua_cocos2dx_experimental_FrameBuffer_getDepthStencilTarget);
        tolua_function(tolua_S,"getClearDepth",lua_cocos2dx_experimental_FrameBuffer_getClearDepth);
        tolua_function(tolua_S,"getClearStencil",lua_cocos2dx_experimental_FrameBuffer_getClearStencil);
        tolua_function(tolua_S,"applyFBO",lua_cocos2dx_experimental_FrameBuffer_applyFBO);
        tolua_function(tolua_S,"setClearStencil",lua_cocos2dx_experimental_FrameBuffer_setClearStencil);
        tolua_function(tolua_S,"getRenderTarget",lua_cocos2dx_experimental_FrameBuffer_getRenderTarget);
        tolua_function(tolua_S,"getHeight",lua_cocos2dx_experimental_FrameBuffer_getHeight);
        tolua_function(tolua_S,"clearFBO",lua_cocos2dx_experimental_FrameBuffer_clearFBO);
        tolua_function(tolua_S,"init",lua_cocos2dx_experimental_FrameBuffer_init);
        tolua_function(tolua_S,"isDefaultFBO",lua_cocos2dx_experimental_FrameBuffer_isDefaultFBO);
        tolua_function(tolua_S,"setClearColor",lua_cocos2dx_experimental_FrameBuffer_setClearColor);
        tolua_function(tolua_S,"getFBO",lua_cocos2dx_experimental_FrameBuffer_getFBO);
        tolua_function(tolua_S,"getClearColor",lua_cocos2dx_experimental_FrameBuffer_getClearColor);
        tolua_function(tolua_S,"attachRenderTarget",lua_cocos2dx_experimental_FrameBuffer_attachRenderTarget);
        tolua_function(tolua_S,"attachDepthStencilTarget",lua_cocos2dx_experimental_FrameBuffer_attachDepthStencilTarget);
        tolua_function(tolua_S,"newImage",lua_cocos2dx_experimental_FrameBuffer_newImage);
        tolua_function(tolua_S,"setClearDepth",lua_cocos2dx_experimental_FrameBuffer_setClearDepth);
        tolua_function(tolua_S,"setSize",lua_cocos2dx_experimental_FrameBuffer_setSize);
        tolua_function(tolua_S,"getOrCreateDefaultFBO", lua_cocos2dx_experimental_FrameBuffer_getOrCreateDefaultFBO);
        tolua_function(tolua_S,"create", lua_cocos2dx_experimental_FrameBuffer_create);
        tolua_function(tolua_S,"applyDefaultFBO", lua_cocos2dx_experimental_FrameBuffer_applyDefaultFBO);
        tolua_function(tolua_S,"clearAllFBOs", lua_cocos2dx_experimental_FrameBuffer_clearAllFBOs);
        tolua_function(tolua_S,"getDefaultFBO", lua_cocos2dx_experimental_FrameBuffer_getDefaultFBO);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::FrameBuffer).name();
    g_luaType[typeName] = "ccexp.FrameBuffer";
    g_typeCast["FrameBuffer"] = "ccexp.FrameBuffer";
    return 1;
}
TOLUA_API int register_all_cocos2dx_experimental(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccexp",0);
	tolua_beginmodule(tolua_S,"ccexp");

	lua_register_cocos2dx_experimental_RenderTarget(tolua_S);
	lua_register_cocos2dx_experimental_TMXTiledMap(tolua_S);
	lua_register_cocos2dx_experimental_RenderTargetRenderBuffer(tolua_S);
	lua_register_cocos2dx_experimental_TMXLayer(tolua_S);
	lua_register_cocos2dx_experimental_FrameBuffer(tolua_S);
	lua_register_cocos2dx_experimental_RenderTargetDepthStencil(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

