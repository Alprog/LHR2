#ifndef __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__
#define __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

#include "ui/lua_cocos2dx_ui_manual.hpp"
#include "cocosdenshion/lua_cocos2dx_cocosdenshion_manual.h"
#include "3d/lua_cocos2dx_3d_manual.h"
#include "cocostudio/lua_cocos2dx_coco_studio_manual.hpp"
#include "audioengine/lua_cocos2dx_audioengine_manual.h"

int lua_module_register(lua_State* L)
{
	register_ui_moudle(L);
    register_cocosdenshion_module(L);
	register_cocostudio_module(L);
	register_cocos3d_module(L);
	register_audioengine_module(L);
	return 1;
}

#endif  // __TEST_LUA_TESTS_PROJECT_CLASSES_LUA_MODULE_REGISTER_H__

