 
Timeline = Derive('Timeline', PinBoard)

local pinHeight = 16

function Timeline:init()
    Timeline.base.init(self)    
    self.cursor = cc.Sprite:create('pixel.png')
    self:addChild(self.cursor)
    self.itemSelected = Event:create()
    self.particlesEditing = Event:create()
end

function Timeline:setAnimate(animate)
    if self.animate ~= animate then
        self.animate = animate
        self:selectItem(nil)
        self:refresh()
    end
end

function Timeline:onSelectPin(pin)
    self:selectItem(pin.action)    
end

function Timeline:selectItem(item)
    self.selectedItem = item
    self.itemSelected:raise(self, item)
    self:refresh()
end

function Timeline:update(delta)
    PinBoard.update(self, delta)
    self:updateCursor()
end

function Timeline:addSoundAction()
    self:addAnimateAction('SoundEffect', 'shot.ogg')
end

function Timeline:addParticlesAction()
    self:addAnimateAction('ParticlesEffect', 'particles/explode.prt')
end

function Timeline:addAnimateAction(type, filePath)
    local action = AnimateAction:create(type, self.animate.time, filePath)
    table.insert(self.animate.actions, action)
    self:refresh()
end

function Timeline:onKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_DELETE then
        local action = self.selectedItem
        if action then
            table.removeValue(self.animate.actions, action)
            self:refresh()
        end
    elseif keyCode == cc.KeyCode.KEY_S then
        self:addSoundAction()
    elseif keyCode == cc.KeyCode.KEY_P then
        self:addParticlesAction()
    elseif keyCode == cc.KeyCode.KEY_E then
        local action = self.selectedItem
        if action and action.type == 'ParticlesEffect' then
            self.particlesEditing:raise(action.filePath)
        end
    end
end

function Timeline:updateCursor()
    local animate = self.animate
    if animate then
        local size = self:getContentSize()
        local x = animate.time * size.width / animate.duration
        self.cursor:setPosition(x, size.height / 2)
        self.cursor:setScale(1, size.height)
    end
    self.cursor:setVisible(animate ~= nil)
end

function Timeline:onDoubleClick(position)
    self:addParticlesAction()
end

function Timeline:onClick(position)
    local time = self:getTimeFromPosition(position)
    self.animate:setTime(time)
end

function Timeline:getPositionFromTime(time)
    local width = self:getContentSize().width
    return time * width / self.animate.duration
end

function Timeline:getTimeFromPosition(position)
    local size = self:getContentSize()
    local k = position.x / size.width
    return k * self.animate.duration
end

function Timeline:createPin()
    return TimelinePin:create() 
end

function Timeline:onPinDrag(pos)
   local action = self.selectedItem
   local index = table.indexOf(self.animate.actions, action)
   local time = self:getTimeFromPosition(pos)
   time = clamp(time, 0, self.animate.duration)
   action.time = time
   self:refresh()
end

function Timeline:refresh()  
    local animate = self.animate
    
    if not animate then
        self:setPinCount(0)
        return
    end

    local size = self:getContentSize()
    local actions = animate.actions
    self:setPinCount(#actions)
    
    local k = size.width / animate.duration
    
    local y = size.height
    
    for i = 1, #actions do
        local action = actions[i]
        local pin = self.pins[i]
        
        pin:setAction(action)
        pin:setSelection(action == self.selectedItem)
        
        local x = action.time * k
        local width = clamp(action:getDuration() * k, pinHeight, size.width - x)
        
        pin:setSize(cc.size(width, pinHeight))
        pin:setPosition(x, y)
        
        y = y - (pinHeight + 1)
    end
end



