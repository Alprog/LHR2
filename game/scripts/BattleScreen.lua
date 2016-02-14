
require 'Battle.lua'
require 'FrameBuffer.lua'
require 'Marine.lua'
require 'BigRobot.lua'
require 'Mechanic.lua'
require 'Renegade.lua'
require 'Avatar.lua'

BattleScreen = Derive('BattleScreen', Scene)

MASK_LAYER = cc.CameraFlag.USER1

function BattleScreen:init()
    Scene.init(self, 'BattleScreen')
    
    self:scheduleUpdate()
    self:initUI()
   
    local battle = Battle:create()
    battle:setTeamCount(2)
    for i = 1, 4 do
        local mechanic = Mechanic:create()
        table.insert(battle.teams[2], mechanic)
    end
    for i = 1, 2 do
        local mechanic = Mechanic:create()
        table.insert(battle.teams[1], mechanic)
    end
    
    self.arena = Arena:create()
    
    WithoutDebug(function()
        self.arena:createTerrain()
    end)
    
    --arena:addObstacles()
            
    self.arena:update(0)
    
    self:getChildByName('ArenaLayer'):addChild(self.arena)
    
    
    battle:setArena(self.arena)
    battle:setScene(self)
    
    battle:spawnTeams()
    
    local touchBeginPoint = nil
    
    local function onTouchBegan(touch, event)
        local location = touch:getLocation()
        touchBeginPoint = {x = location.x, y = location.y}
        return true
    end
        
    self.battle:selectPlayerByIndex(1)
    self:updateUI()
end

function BattleScreen:initUI()
    self.actionPanel = self:getChildByName('ActionPanel')
    self:initAvatars() 
end

function BattleScreen:initAvatars()
    self.avatars = {}
    
    local panel = self:getChildByName('AvatarPanel')
    local children = panel:getChildren()
    for i = 1, #children do
        local child = children[i]
        local name = child:getName()
        if name:startWith('Avatar') then
            local index = tonumber(name:sub(-1))
            local avatar = Avatar:create(child, index)          
            self:regButton(avatar.button)
            self.avatars[index] = avatar
        end
    end
end

function BattleScreen:update(dt)
end

function BattleScreen:render()
    self.arena:render()    
    Scene.render(self)
end

function BattleScreen:onKeyPress(keyCode)
    if keyCode == cc.KeyCode.KEY_F2 then
        local visible = self.maskSprite:isVisible()
        self.maskSprite:setVisible(not visible)
    elseif keyCode == cc.KeyCode.KEY_SPACE then
        self.battle:selectNext()
        self:updateUI()
    else
        Scene.onKeyPress(self, keyCode)
    end
end

function BattleScreen:onButtonClick(button)
    local name = button:getName()
    print(name)
    if name == 'MenuButton' then
        theSceneManager:push(Menu:create())
    elseif name == 'AvatarButton' then
        self.battle:selectPlayerByIndex(button.index)
    elseif name == 'MotionButton' then
        self.battle:toggleMode('motion')
    elseif name == 'AttackButton' then
        self.battle:toggleMode('attack')
    elseif name == 'TurnLeftButton' then
        self.battle:turnPlayer(1)
    elseif name == 'TurnRightButton' then
        self.battle:turnPlayer(-1)
    elseif name == 'EndRoundButton' then
        self.battle:endRound()
    end
    
    self:updateUI()
end

function BattleScreen:onResize(size)
    Scene.onResize(self, size)
    self.arena:onResize(size)
    self:SetMaskSprite()
end

function BattleScreen:SetMaskSprite()
    local visible = self.maskSprite and self.maskSprite:isVisible()
    if self.maskSprite then
        self.maskSprite:removeFromParent()
    end
    self.maskSprite = cc.Sprite:createWithTexture(self.arena.fb:getTexture())
    self.maskSprite:setAnchorPoint(Vec(0.5, 0.5))
    
    self.maskSprite:setPosition3D(Vec(0, 0, 0))
    self:addChild(self.maskSprite)
    self.maskSprite:setVisible(visible)
    
    local height = self.maskSprite:getContentSize().height
    local scale = 768 / height
    self.maskSprite:setScale(scale, -scale)
    self.maskSprite:setLocalZOrder(-1)
end

function BattleScreen:destroy()
    self.arena:destroy()
    self.arena = nil
end

function BattleScreen:updateUI()
    local team = self.battle.currentTeam
    for i = 1, #self.avatars do
        local avatar = self.avatars[i]
        avatar:setUnit(team[i])
    end
    self.actionPanel:setVisible(self.battle.player ~= nil)
end
