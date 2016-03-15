
LevelEditor = Derive('LevelEditor', Scene)

function LevelEditor:init()
    Scene.init(self, 'LevelEditor')
    
    self:scheduleUpdate()
    
    self.scene3D = Scene3D:create()
    theApp.scene:addChild(self.scene3D)
    self:enableNodeEvents()
    
    self.projector = Projector:create(self:getChildByName('3DScreen'))
    self.projector:addSource(theRenderer, 'primaryTexture')
    self.projector:addSource(theRenderer, 'albedoTexture')
    self.projector:addSource(theRenderer, 'normalTexture')
    self.projector:addSource(theRenderer, 'idsTexture')
    self.projector:addSource(theRenderer, 'velocityTexture')
    self.projector:addSource(theRenderer, 'depthTexture', 'depth')
    self.projector:addSource(theRenderer, 'shadowMapTexture', 'depth')
    
    self.mapProjector = Projector:create(self:getChildByName('MapScreen'))
    self.mapProjector:addSource(theRenderer, 'auxTexture')
     
    local touchBeginPoint = nil
    
    local function onTouchBegan(touch, event)
        local location = touch:getLocation()
        touchBeginPoint = {x = location.x, y = location.y}
        return true
    end
    
    WithoutDebug(function()
        self.level = Level:create()
        self.scene3D:addChild(self.level)
    end)

    self:listenTouches()
end

function LevelEditor:onCleanup()
    if theApp.running then
        self.scene3D:removeFromParent()
    end
end

function LevelEditor:update(dt)
    if not self.a then
        self.a = true
    else
        self.scene3D:checkHover()
    end
    
    local object = self.scene3D.hoveredObject
    if object then
        local corners = Input.keys[cc.KeyCode.KEY_CTRL]
        local sides = Input.keys[cc.KeyCode.KEY_SHIFT]
        local affectNeighbors = Input.keys[cc.KeyCode.KEY_ALT]
        object:setHighlight(corners, sides, affectNeighbors, self.scene3D.camera)
    end

    if self.lightControl then
        self.scene3D.lightCamera.free = true
        self.scene3D.lightCamera:update(dt)
    else
        self.scene3D.camera:update(dt)
        self.scene3D.target:update(dt)
    end
    
    self.projector:refreshScreen()
end

function LevelEditor:render()
    self.scene3D:render()
    Scene.render(self)
end

function LevelEditor:onKeyPress(keyCode)
    if keyCode == KEY_F2 then
        self.projector:nextSource()
    elseif keyCode == KEY_F6 then
        self:saveLevel()
    elseif keyCode == KEY_F8 then
        self:loadLevel()
    else
        Scene.onKeyPress(self, keyCode)
    end
    
    if keyCode == KEY_TAB then
        self.lightControl = not self.lightControl
    end
    
    local block = self.scene3D.hoveredObject
    if block then
        self:onBlockKeyPress(block, keyCode)
    end
end

function LevelEditor:saveLevel()
    serializeToFile(self.level, 'level.ini')
end

function LevelEditor:loadLevel()
    self.scene3D:clearHovered()
    self.level:removeFromParent()
    self.level = deserializeFromFile('level.ini')
    self.scene3D:addChild(self.level)
end

function LevelEditor:onBlockKeyPress(block, keyCode)
    if keyCode == cc.KeyCode.KEY_SPACE then
        block:changeTexture()
    elseif keyCode == cc.KeyCode.KEY_LEFT_BRACKET then
        block:addScale(-0.01)
    elseif keyCode == cc.KeyCode.KEY_RIGHT_BRACKET then
        block:addScale(0.01)
    end
end

function LevelEditor:onButtonClick(button)
    local name = button:getName()
    if name == 'MenuButton' then
        theSceneManager:push(Menu:create())
    end
end

function LevelEditor:onResize(size)
    Scene.onResize(self, size)
    self.scene3D:onResize(size)
    self.projector:refreshScreen()
    self.mapProjector:refreshScreen()
end

function LevelEditor:onTouchEnded(touch, event)
   
    if self.scene3D.hoveredObject then
        local object = self.scene3D.hoveredObject
        
        print('id', touch:getButtonId())
        
        if object.className == 'Block' then
            local value = 0.25 * (touch:getButtonId() == 0 and 1 or -1)
            object:extrude(value)
        end
        self.level:refreshGfx()
    end
end

