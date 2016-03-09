
require 'cocos/init.lua'
require 'cocos/framework/init.lua'
require 'Debug.lua'
require 'NodeExtension.lua'
require 'Sprite3DExtension.lua'
require 'Class.lua'
require 'Utils.lua'
require 'Serialize.lua'
require 'App.lua'
require 'SceneManager.lua'
require 'PostProcessor.lua'
require 'Scene.lua'

require 'Vector.lua'
require 'Input.lua'
require 'Audio.lua'
require 'Arena.lua'
require 'Scene3D.lua'

require 'cache/init.lua'
require 'properties/init.lua'
require 'Event.lua'
require 'CurryFunc.lua'

require 'Parameter.lua'
require 'SplashScreen.lua'
require 'TitleScreen.lua'
require 'BattleScreen.lua'
require 'LevelEditor.lua'
require 'Menu.lua'
require 'EffectLab.lua'
require 'Carcase.lua'
require 'ParticlesEffect.lua'
require 'Projector.lua'
require 'RenderMode.lua'
require 'Material.lua'

require 'Level.lua'
require 'Section.lua'
require 'Renderer.lua'

require 'ContentPipeline.lua'
contentPipeline()

cc.Node.className = 'cc.Node'
cc.Sprite3D.className = 'cc.Sprite3D'
cc.AttachNode.className = 'cc.AttachNode'
cc.GLProgramState.className = 'cc.GLProgramState'
cc.Material.className = 'cc.Material'
cc.Technique.className = 'cc.Technique'
cc.Pass.className = 'cc.Pass'

local function main()
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    math.randomseed(os.time())
       
    theApp = App:create("Little Humble RPG 2")
    theSceneManager = theApp.sceneManager
    theRenderer = theApp.renderer
    thePostProcessor = theApp.postProcessor
    
    local screen = nil
    if theApp.settings.splash then
        screen = SplashScreen:create()
    else
        screen = TitleScreen:create()
    end
    theSceneManager:goTo(screen)
end

function render()
    theSceneManager:render()    
end

xpcall(main, __G__TRACKBACK__)


