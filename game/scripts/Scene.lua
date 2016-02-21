
Scene = Derive('Scene', cc.Node)

local minVirtualWidth = 1024
local maxVirtualWidth = 1366
local virtualHeight = 768
local startFrame = 0
local endFrame = 24

function Scene:init(filename)
    if filename then
        self.path = "scenes/"..filename..".csb"
        local root = cc.CSLoader:createNode(self.path)
        local children = root:getChildren()
        for i = 1, #children do
            local child = children[i]
            child:removeFromParent()
            self:addChild(child)
        end
    end
    
    self:removeBorders()
    self:setButtonHandlers()
end

function Scene:onEnter()
    self.enabled = true
end

function Scene:onExit()
    self.enabled = false
end

function Scene:removeBorders()
    local borders = self:getChildByName('Borders')
	if borders then
		borders:removeFromParent()
	end
end

function Scene:setButtonHandlers()
    local buttons = self:selectChildren(function(child)
        return is(child, ccui.Button) or is(child, ccui.CheckBox)
    end)
    
    for i = 1, #buttons do
        local button = buttons[i]
        local str = button:getUserString()
        if str ~= "" then
            button.hotKeyCode = cc.KeyCode['KEY_'..str]
        end
        self:regButton(button)
    end
end

function Scene:regButton(button)
    self.buttons = self.buttons or {}
    self:listenButtonClick(button)
    table.insert(self.buttons, button) 
end

function Scene:onButtonClick(button)
    print('click '..button:getName())
end

function Scene:onKeyPress(keyCode)
    for i = 1, #self.buttons do
        local button = self.buttons[i]
        if button:isEnabled() and button:isVisibleAtScene() then
            if button.hotKeyCode == keyCode then
                self:onButtonClick(button)
                return true
            end
        end
    end
end

function Scene:onResize(size) 
    local scale = size.height / virtualHeight
    if self.path then
        local needWidth = size.width / scale
        local k = (needWidth - maxVirtualWidth) / (minVirtualWidth - maxVirtualWidth)
        k = clamp(k, 0, 1)
        local frame = round(k * endFrame)
        
        local timeline = cc.CSLoader:createTimeline(self.path)
        timeline:startWithTarget(self)
        timeline:gotoFrameAndPause(frame)
    end
    
    if self.controlTies then
        
        for control, area in pairs(self.controlTies) do
            local size = area:getContentSize()
            size.width = size.width * area:getScaleX()
            size.height = size.height * area:getScaleY()
            
            control:setContentSize(size)
            control:setPosition(area:getPosition())
            control:setAnchorPoint(area:getAnchorPoint())
            
            if control.onResize then
                control:onResize(size)
            end
        end
    end
end

function Scene:tie(control, area)
    self.controlTies = self.controlTies or {}
    if type(area) == 'string' then
        area = self:getChildByName(area)
    end
    self.controlTies[control] = area
    area:setVisible(false)
    
    control:removeFromParent()
    
    area:getParent():addChild(control)
end

function Scene:show()
    theSceneManager:push(self)
end

function Scene:showAndWait()
    self:retain()
    theSceneManager:push(self)
    while self:getParent() do
        coroutine.yield()
    end
    local result = self.result
    self:release()
    return result
end

function Scene:close(result)
    self.result = result
    theSceneManager:pop() 
end

function Scene:render()
    theSceneManager.defaultCamera:render(self, cc.CameraFlag.DEFAULT)
end
