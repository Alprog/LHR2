
Avatar = Class('Avatar')

function Avatar:init(node, index)
    node:mapChildrenTo(self)
    
    local button = self.avatarButton
    button.index = index
    button.hotKeyCode = cc.KeyCode['KEY_'..index]
    self.button = button
    
    self.hotkeyLabel:setString(index)
    
    self.gfx = node
end

function Avatar:setUnit(unit)
    if unit and not unit.dead then
        self.gfx:setVisible(true)
        self:setPortrait(unit.portraitName)
        self.background:setColor(unit.selected and cc.YELLOW or cc.WHITE)
        self.healthBar:setPercent(unit.healthPoints:getPercents())
        self.motionBar:setPercent(unit.motionPoints:getPercents())
        self.actionBar:setPercent(unit.actionPoints:getPercents())
    else
        self.gfx:setVisible(false)
    end
end

function Avatar:setPortrait(name)
    local texture = getTexture('portraits/'.. name ..'.png')
    self.portrait:setTexture(texture)
end