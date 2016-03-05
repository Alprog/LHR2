
LevelEditor = Derive('LevelEditor', Scene)

function LevelEditor:init()
    Scene.init(self, 'LevelEditor')
    
    self:scheduleUpdate()
    
    self.scene3D = Scene3D:create()
    theApp.scene:addChild(self.scene3D)
    self:enableNodeEvents()
    
    self.projector = Projector:create(self:getChildByName('3DScreen'))
    self.projector:addSource(self.scene3D.frameBuffer, 0)
    self.projector:addSource(self.scene3D.gBuffer, GBuffer.Index.Albedo)
    self.projector:addSource(self.scene3D.gBuffer, GBuffer.Index.Normal)
    self.projector:addSource(self.scene3D.gBuffer, GBuffer.Index.Ids)
    self.projector:addSource(self.scene3D.gBuffer, GBuffer.Index.Velocity)
    self.projector:addSource(self.scene3D.gBuffer, GBuffer.Index.DepthStencil, 'depth')
    self.projector:addSource(self.scene3D.shadowMapBuffer, FrameBuffer.Index.DepthStencil, 'depth')
     
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
    self.scene3D:checkHover()
    local object = self.scene3D.hoveredObject
    if object then
        local corners = Input.keys[cc.KeyCode.KEY_CTRL]
        local sides = Input.keys[cc.KeyCode.KEY_SHIFT]
        local affectNeighbors = Input.keys[cc.KeyCode.KEY_ALT]
        object:setHighlight(corners, sides, affectNeighbors, self.scene3D.camera)
    end
end

function LevelEditor:render()
    self.scene3D:render()
    Scene.render(self)
end

function LevelEditor:onKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_F2 then
        self.projector:nextSource()
    elseif keyCode == cc.KeyCode.KEY_F6 then
        self:saveLevel()
    elseif keyCode == cc.KeyCode.KEY_F8 then
        self:loadLevel()
    else
        Scene.onKeyPress(self, keyCode)
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
   if keyCode == cc.KeyCode.KEY_Z then
        block:skew(-1)
    elseif keyCode == cc.KeyCode.KEY_X then
        block:skew(1)
    elseif keyCode == cc.KeyCode.KEY_C then
        block:rotate()
    elseif keyCode == cc.KeyCode.KEY_V then
        block:setScaleZ(0.5)
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

