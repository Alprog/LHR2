
ControlPanel = Derive('ControlPanel', Scene)

function ControlPanel:instantinate()
    return ControlPanel.__create()
end

function ControlPanel:init(scene)   
    Scene.init(self, 'ControlPanel')
    self.scene = scene
    
    local panel = self:getChildByName('Panel')
    self.playButton = panel:getChildByName('PlayButton')
    self.loopCheckBox = panel:getChildByName('LoopCheckBox')
    self:setContentSize(panel:getContentSize())
    
    self:scheduleUpdate()
end

function ControlPanel:update()
    self.playButton:setTitleText(self.scene:isPlaying() and 'II' or '>')
    self.loopCheckBox:setSelected(self.scene:isLoop())
end

function ControlPanel:onButtonClick(button)
    local animate = self.scene:getCurAnimate()
    if not animate then
        return
    end
    
    local name = button:getName()
    if name == 'PlayButton' then
        animate:togglePause()
    elseif name == 'HomeButton' then
        animate:goToStart()
    elseif name == 'EndButton' then
        animate:goToEnd()
    elseif name == 'LoopCheckBox' then
        animate:toggleLoop()
    end
end