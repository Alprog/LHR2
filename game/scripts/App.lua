
App = Class('App')

local settingsPath = '../settings.lua'

function App:init(name)
    self.director = cc.Director:getInstance()
    self:loadSettings()
    self:initView(name)
    self:updateView()
    self:run()
end

function App:loadSettings()
    self.settings = loadTableFromFile(settingsPath, 'settings') or {}
    
    setDefaults(self.settings, {
        fullscreen = true,
        width = 1366,
        height = 768,
        sound = true,
        music = true,
        splash = true,
        statistics = false
    })
end

function App:saveSettings()
    saveTableToFile(self.settings, settingsPath, 'settings')
end

function App:initView(name)
    self.view = cc.GLViewImpl:create(name)
    self.director:setOpenGLView(self.view)
end

function App:updateView()
    if self.settings.fullscreen then
        self.view:setFrameSize(0, 0)
    else
        local width = self.settings.width
        local height = self.settings.height
        self.view:setFrameSize(width, height)
    end
    
    self.windowSize = self.view:getFrameSize()
    self:updateDesignResolution()
    self.view:setViewPortInPoints(0, 0, self.windowSize.width, self.windowSize.height)
end

function App:updateDesignResolution()
    self.view:setDesignResolutionSize(self.windowSize.width, self.windowSize.height, cc.ResolutionPolicy.NO_BORDER)
end

function App:run(sceneManager)
    self.director:setProjection(cc.DIRECTOR_PROJECTION2_D)
    self.director:setDisplayStats(self.settings.statistics)
    self.director:setAnimationInterval(1.0 / 60)
    
    self.sceneManager = SceneManager:create(self)
    self.scene = cc.Scene:create()
    self.scene:addChild(self.sceneManager.root)
    
    self.scene:getDefaultCamera():setScene(self.scene)
    
    self.director:runWithScene(self.scene)
    self:updateDesignResolution()
    
    self.director:setDepthTest(false)
    
    self.tasks = TaskManager:create()
    self.scene:scheduleUpdateWithPriorityLua(function(dt)
        self.tasks:update(dt)
    end, 0)
end

function App:toggleStatistics()
    self.settings.statistics = not self.settings.statistics
    self.director:setDisplayStats(self.settings.statistics)
    self:saveSettings()
end

function App:toggleFullscreen()
    self.settings.fullscreen = not self.settings.fullscreen
    self:updateView()
    self:saveSettings()
    self.sceneManager:refreshSize()
end

function App:toggleWidescreen()
    if not self.settings.fullscreen then
        local size = Vec(self.settings.width, self.settings.height)
        
        local aspect = size.x / size.y
        local quadAspect = 4 / 3
        local wideAspect = 16 / 9
        
        local wide = aspect > (quadAspect + wideAspect) / 2 
        
        local newAspect = wide and quadAspect or wideAspect
        size.x = math.ceil(size.y * newAspect)
        
        self.settings.width = size.x
        self.settings.height = size.y
        self:updateView()
        self:saveSettings()
        
        self.sceneManager:refreshSize()
    end
end

function App:setCursorVisible(value)
    self.view:setCursorVisible(value)
end

function App:close()
    cc.Director:getInstance():endToLua()
end