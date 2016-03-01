
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
end

function LevelEditor:onCleanup()
    if theApp.running then
        self.scene3D:removeFromParent()
    end
end

function LevelEditor:update(dt)
end

function LevelEditor:render()
    self.scene3D:render()    
    Scene.render(self)
end

function LevelEditor:onKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_F2 then
        self.projector:nextSource()
    else
        Scene.onKeyPress(self, keyCode)
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
