
GameScreen = Derive('GameScreen', Scene)

function GameScreen:init()
    Scene.init(self, 'LevelEditor')
    
    self:scheduleUpdate()
    
    self.scene3D = Scene3D:create()
    theApp.scene:addChild(self.scene3D)
    
    self.projector = Projector:create(self:getChildByName('3DScreen'))
    self.projector:addSource(theRenderer, 'primaryTexture', 'opaque')
    
    WithoutDebug(function()
        self.level = Level:create()
        self.scene3D:addChild(self.level)
        self:loadLevel()
    end)

    self:listenTouches()
    
    self.warrior = Warrior:create()
    self.level:addChild(self.warrior)
    self.warrior:setPosition3D(Vec(2, 0, 4))
end

function GameScreen:onKill()
    self.scene3D:removeFromParent()
end

function GameScreen:update(dt)
    self.scene3D:checkHover()

    if theControl.buttonSelect:onPress() then
        self.playerControl = not self.playerControl
    end

    if self.playerControl then
        self:playerUpdate(dt)
    else
        self.scene3D.camera:update(dt)
        self.scene3D.target:update(dt)
    end
end

function GameScreen:playerUpdate(dt)
    local value = theControl.trackMove:getValue()
    local position = self.warrior:getPosition3D()
    position.x = position.x + value.x * dt
    position.z = position.z + value.z * dt
    self.warrior:setPosition3D(position)
end

function GameScreen:render()
    self.scene3D:render()
    self.projector:refreshScreen()
    Scene.render(self)
end

function GameScreen:loadLevel()
    self.scene3D:clearHovered()
    self.level:removeFromParent()
    self.level = deserializeFromFile('level.ini')
    self.scene3D:addChild(self.level)
end

function GameScreen:onButtonClick(button)
    local name = button:getName()
    if name == 'MenuButton' then
        theSceneManager:push(Menu:create())
    end
end

function GameScreen:onResize(size)
    Scene.onResize(self, size)
    self.scene3D:onResize(size)
    self.projector:refreshScreen()
end

function GameScreen:onTouchEnded(touch, event)

end

