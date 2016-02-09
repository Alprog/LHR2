#include "lua_cocos2dx_particles_auto.hpp"
#include "cocos2d.h"
#include "particles.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_cocos2dx_particles_ParticleSystemNode_setTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Texture2D* arg0;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.ParticleSystemNode:setTexture");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_setTexture'", nullptr);
            return 0;
        }
        cobj->setTexture(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:setTexture",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_getTexture(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_getTexture'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_getTexture'", nullptr);
            return 0;
        }
        cocos2d::Texture2D* ret = cobj->getTexture();
        object_to_luaval<cocos2d::Texture2D>(tolua_S, "cc.Texture2D",(cocos2d::Texture2D*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:getTexture",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_getTexture'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_isFull(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_isFull'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_isFull'", nullptr);
            return 0;
        }
        bool ret = cobj->isFull();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:isFull",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_isFull'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_isBlendAdditive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_isBlendAdditive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_isBlendAdditive'", nullptr);
            return 0;
        }
        bool ret = cobj->isBlendAdditive();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:isBlendAdditive",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_isBlendAdditive'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_setBlendAdditive(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendAdditive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.ParticleSystemNode:setBlendAdditive");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendAdditive'", nullptr);
            return 0;
        }
        cobj->setBlendAdditive(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:setBlendAdditive",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendAdditive'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_setTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_setTotalParticles'", nullptr);
            return 0;
        }
        cobj->setTotalParticles(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:setTotalParticles",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setTotalParticles'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_getParticleCount(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_getParticleCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_getParticleCount'", nullptr);
            return 0;
        }
        int ret = cobj->getParticleCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:getParticleCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_getParticleCount'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_getBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_getBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_getBlendFunc'", nullptr);
            return 0;
        }
        const cocos2d::BlendFunc& ret = cobj->getBlendFunc();
        blendfunc_to_luaval(tolua_S, ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:getBlendFunc",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_getBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_updateTexCoords(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_updateTexCoords'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_updateTexCoords'", nullptr);
            return 0;
        }
        cobj->updateTexCoords();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:updateTexCoords",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_updateTexCoords'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_setParameterGraph(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setParameterGraph'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 4) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg1;
            ok &= luaval_to_std_vector_float(tolua_S, 3, &arg1, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg2;
            ok &= luaval_to_std_vector_float(tolua_S, 4, &arg2, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg3;
            ok &= luaval_to_std_vector_float(tolua_S, 5, &arg3, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            cobj->setParameterGraph(arg0, arg1, arg2, arg3);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg1;
            ok &= luaval_to_std_vector_float(tolua_S, 3, &arg1, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg2;
            ok &= luaval_to_std_vector_float(tolua_S, 4, &arg2, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            cobj->setParameterGraph(arg0, arg1, arg2);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 5) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg1;
            ok &= luaval_to_std_vector_float(tolua_S, 3, &arg1, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg2;
            ok &= luaval_to_std_vector_float(tolua_S, 4, &arg2, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg3;
            ok &= luaval_to_std_vector_float(tolua_S, 5, &arg3, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg4;
            ok &= luaval_to_std_vector_float(tolua_S, 6, &arg4, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            cobj->setParameterGraph(arg0, arg1, arg2, arg3, arg4);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 6) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg1;
            ok &= luaval_to_std_vector_float(tolua_S, 3, &arg1, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg2;
            ok &= luaval_to_std_vector_float(tolua_S, 4, &arg2, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg3;
            ok &= luaval_to_std_vector_float(tolua_S, 5, &arg3, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg4;
            ok &= luaval_to_std_vector_float(tolua_S, 6, &arg4, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            std::vector<float, std::allocator<float> > arg5;
            ok &= luaval_to_std_vector_float(tolua_S, 7, &arg5, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            cobj->setParameterGraph(arg0, arg1, arg2, arg3, arg4, arg5);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            IParameter* arg1;
            ok &= luaval_to_object<IParameter>(tolua_S, 3, "IParameter",&arg1, "cc.ParticleSystemNode:setParameterGraph");

            if (!ok) { break; }
            cobj->setParameterGraph(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    }while(0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n",  "cc.ParticleSystemNode:setParameterGraph",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setParameterGraph'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_getSettings(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_getSettings'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ParticleSystemNode:getSettings");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_getSettings'", nullptr);
            return 0;
        }
        SystemSettings ret = cobj->getSettings(arg0);
        #pragma warning NO CONVERSION FROM NATIVE FOR SystemSettings;
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:getSettings",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_getSettings'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_allocMemory(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_allocMemory'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_allocMemory'", nullptr);
            return 0;
        }
        bool ret = cobj->allocMemory();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:allocMemory",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_allocMemory'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_step(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_step'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.ParticleSystemNode:step");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_step'", nullptr);
            return 0;
        }
        cobj->step(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:step",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_step'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_reset(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_reset'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_reset'", nullptr);
            return 0;
        }
        cobj->reset();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:reset",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_reset'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_setBlendFunc(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendFunc'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::BlendFunc arg0;

        ok &= luaval_to_blendfunc(tolua_S, 2, &arg0, "cc.ParticleSystemNode:setBlendFunc");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendFunc'", nullptr);
            return 0;
        }
        cobj->setBlendFunc(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:setBlendFunc",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setBlendFunc'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_initTexCoordsWithRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_initTexCoordsWithRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Rect arg0;

        ok &= luaval_to_rect(tolua_S, 2, &arg0, "cc.ParticleSystemNode:initTexCoordsWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_initTexCoordsWithRect'", nullptr);
            return 0;
        }
        cobj->initTexCoordsWithRect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:initTexCoordsWithRect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_initTexCoordsWithRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_setTextureWithRect(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_setTextureWithRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Texture2D* arg0;
        cocos2d::Rect arg1;

        ok &= luaval_to_object<cocos2d::Texture2D>(tolua_S, 2, "cc.Texture2D",&arg0, "cc.ParticleSystemNode:setTextureWithRect");

        ok &= luaval_to_rect(tolua_S, 3, &arg1, "cc.ParticleSystemNode:setTextureWithRect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_setTextureWithRect'", nullptr);
            return 0;
        }
        cobj->setTextureWithRect(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:setTextureWithRect",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_setTextureWithRect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_initIndices(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_initIndices'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_initIndices'", nullptr);
            return 0;
        }
        cobj->initIndices();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:initIndices",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_initIndices'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_initWithTotalParticles(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::ParticleSystemNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::ParticleSystemNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_particles_ParticleSystemNode_initWithTotalParticles'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:initWithTotalParticles");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_initWithTotalParticles'", nullptr);
            return 0;
        }
        bool ret = cobj->initWithTotalParticles(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.ParticleSystemNode:initWithTotalParticles",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_initWithTotalParticles'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_particles_ParticleSystemNode_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.ParticleSystemNode",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "cc.ParticleSystemNode:create");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_particles_ParticleSystemNode_create'", nullptr);
            return 0;
        }
        cocos2d::ParticleSystemNode* ret = cocos2d::ParticleSystemNode::create(arg0);
        object_to_luaval<cocos2d::ParticleSystemNode>(tolua_S, "cc.ParticleSystemNode",(cocos2d::ParticleSystemNode*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.ParticleSystemNode:create",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_particles_ParticleSystemNode_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_particles_ParticleSystemNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ParticleSystemNode)");
    return 0;
}

int lua_register_cocos2dx_particles_ParticleSystemNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.ParticleSystemNode");
    tolua_cclass(tolua_S,"ParticleSystemNode","cc.ParticleSystemNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"ParticleSystemNode");
        tolua_function(tolua_S,"setTexture",lua_cocos2dx_particles_ParticleSystemNode_setTexture);
        tolua_function(tolua_S,"getTexture",lua_cocos2dx_particles_ParticleSystemNode_getTexture);
        tolua_function(tolua_S,"isFull",lua_cocos2dx_particles_ParticleSystemNode_isFull);
        tolua_function(tolua_S,"isBlendAdditive",lua_cocos2dx_particles_ParticleSystemNode_isBlendAdditive);
        tolua_function(tolua_S,"setBlendAdditive",lua_cocos2dx_particles_ParticleSystemNode_setBlendAdditive);
        tolua_function(tolua_S,"setTotalParticles",lua_cocos2dx_particles_ParticleSystemNode_setTotalParticles);
        tolua_function(tolua_S,"getParticleCount",lua_cocos2dx_particles_ParticleSystemNode_getParticleCount);
        tolua_function(tolua_S,"getBlendFunc",lua_cocos2dx_particles_ParticleSystemNode_getBlendFunc);
        tolua_function(tolua_S,"updateTexCoords",lua_cocos2dx_particles_ParticleSystemNode_updateTexCoords);
        tolua_function(tolua_S,"setParameterGraph",lua_cocos2dx_particles_ParticleSystemNode_setParameterGraph);
        tolua_function(tolua_S,"getSettings",lua_cocos2dx_particles_ParticleSystemNode_getSettings);
        tolua_function(tolua_S,"allocMemory",lua_cocos2dx_particles_ParticleSystemNode_allocMemory);
        tolua_function(tolua_S,"step",lua_cocos2dx_particles_ParticleSystemNode_step);
        tolua_function(tolua_S,"reset",lua_cocos2dx_particles_ParticleSystemNode_reset);
        tolua_function(tolua_S,"setBlendFunc",lua_cocos2dx_particles_ParticleSystemNode_setBlendFunc);
        tolua_function(tolua_S,"initTexCoordsWithRect",lua_cocos2dx_particles_ParticleSystemNode_initTexCoordsWithRect);
        tolua_function(tolua_S,"setTextureWithRect",lua_cocos2dx_particles_ParticleSystemNode_setTextureWithRect);
        tolua_function(tolua_S,"initIndices",lua_cocos2dx_particles_ParticleSystemNode_initIndices);
        tolua_function(tolua_S,"initWithTotalParticles",lua_cocos2dx_particles_ParticleSystemNode_initWithTotalParticles);
        tolua_function(tolua_S,"create", lua_cocos2dx_particles_ParticleSystemNode_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::ParticleSystemNode).name();
    g_luaType[typeName] = "cc.ParticleSystemNode";
    g_typeCast["ParticleSystemNode"] = "cc.ParticleSystemNode";
    return 1;
}
TOLUA_API int register_all_cocos2dx_particles(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_particles_ParticleSystemNode(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

