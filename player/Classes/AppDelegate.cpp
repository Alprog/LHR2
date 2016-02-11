#include "cocos2d.h"
#include "AppDelegate.h"
#include "audio/include/SimpleAudioEngine.h"
#include "base/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "lua_module_register.h"
#include "resource.h"

USING_NS_CC;
using namespace CocosDenshion;

#if defined(_WIN32)
#include <direct.h>
#endif

AppDelegate::AppDelegate()
{
    // fixed me
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::getInstance()->end();
    //CCScriptEngineManager::destroyInstance();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

void setIcon() 
{
	auto view = Director::getInstance()->getOpenGLView();
	auto hwnd = view->getWin32Window();

	auto icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)icon);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)icon);
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto theFileUtils = FileUtils::getInstance();
	auto paths = theFileUtils->getSearchPaths();

	auto rootDirectory = paths[0];

	// set working directory
#if defined(_WIN32)
	char buffer[512] = { 0 };
	_getcwd(buffer, sizeof(buffer));
	std::string workingDirectory = buffer;
	auto index = workingDirectory.find_last_of('\\');
	rootDirectory = workingDirectory.substr(0, index);
#endif

	paths.clear();
	paths.push_back(rootDirectory + "/data");
	paths.push_back(theFileUtils->getWritablePath());
	theFileUtils->setSearchPaths(paths);

    // register lua engine
    LuaEngine* engine = LuaEngine::getInstance();
	std::string scriptsPath = rootDirectory + "/scripts";
	engine->addSearchPath(scriptsPath.c_str());

    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    lua_module_register(L);

	for (auto& arg : args)
	{
		if (arg == "-debug")
		{
			engine->executeString("debugEnabled = true");
		}
	}

    engine->executeString("require 'main.lua'");

	setIcon();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
