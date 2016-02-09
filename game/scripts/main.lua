
require 'cocos/init.lua'
require 'cocos/framework/init.lua'
require 'Debug.lua'
require 'NodeExtension.lua'
require 'Sprite3DExtension.lua'
require 'Class.lua'
require 'Utils.lua'
require 'App.lua'
require 'SceneManager.lua'
require 'Scene.lua'

require 'Input.lua'
require 'Audio.lua'
require 'Arena.lua'

require 'cache/init.lua'
require 'properties/init.lua'
require 'Event.lua'
require 'CurryFunc.lua'

require 'Parameter.lua'
require 'SplashScreen.lua'
require 'TitleScreen.lua'
require 'BattleScreen.lua'
require 'Menu.lua'
require 'EffectLab.lua'
require 'Carcase.lua'
require 'Vector.lua'
require 'ParticlesEffect.lua'

local function main()
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    math.randomseed(os.time())
    
    theApp = App:create("Little Humble RPG 2")
    theSceneManager = theApp.sceneManager
    
    local screen = nil
    if theApp.settings.splash then
        screen = SplashScreen:create()
    else
        screen = TitleScreen:create()
    end
    theSceneManager:goTo(screen)
end

xpcall(main, __G__TRACKBACK__)


