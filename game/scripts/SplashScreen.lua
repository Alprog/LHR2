
SplashScreen = Derive("SplashScreen", Scene)

function SplashScreen:init()
    self.logo = cc.Sprite:create('logo.png')
    self.logo:setOpacity(0)
    self:addChild(self.logo)
    
    self:scheduleUpdate()
    
    self.tasks = TaskManager:create()
   
    if theApp.settings.fullscreen then
        theApp:setCursorVisible(false)
    end
   
    if theApp.settings.sound then
        self.soundId = Audio:playSound("sounds/splash.ogg")
    end

    self:listenTouches()

    self.tasks:run(function()
        wait(0.2)
        fadeTo(self.logo, 255, 0.8)
        wait(2.2)
        fadeTo(self.logo, 0, 0.8)
        self:goToNextScreen()
    end)
end

function SplashScreen:goToNextScreen()
    if self.soundId then
        Audio:stopSound(self.soundId)
    end
    theSceneManager:goTo(TitleScreen:create())
    theApp:setCursorVisible(true)
end

function SplashScreen:onTouchEnded(touch, event)
    self.tasks:stopAll()
    self:goToNextScreen()
end

function SplashScreen:onKeyPress(keyCode)
    self.tasks:stopAll()
    self:goToNextScreen()
end

function SplashScreen:update(dt)
    self.tasks:update(dt)
end









