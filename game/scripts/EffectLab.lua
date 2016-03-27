
require 'OpenFileDialog.lua'
require 'gui/init.lua'
require 'ParticlesConfig.lua'

EffectLab = Derive('EffectLab', Scene)

local layoutPath = 'labsettings.lua'

function EffectLab:init()
    Scene.init(self, 'EffectLab')
    
    local sheet = cc.Node:create()
    sheet.scaleFactor = 0.45
    self:addChild(sheet)
    
    self:listenWheel()
    
    self.pconfigs = {}
    
    self.animationListView = AnimationListView:create(self)
    
    self:scheduleUpdate()
    self.sheet = sheet
    
    self.mdi = MDI:create()
    self:addChild(self.mdi)
    
    self.mdi:addWindow('Animations', self.animationListView)
    
    self.particlesPanel = ParticlesPanel:create()
    self.particlesPanel.list:setItems(self.pconfigs)
    self.mdi:addWindow('Opened Particles', self.particlesPanel)
    
    self.graph = ParameterGraph:create()
    self.mdi:addWindow('Graph', self.graph)
    
    self.timeline = Timeline:create()
    self.timeline.particlesEditing:bindHandler(self.editParticlesConfig, self)
    self.mdi:addWindow('Timeline', self.timeline)

    self.controlPanel = ControlPanel:create(self)
    self.mdi:addWindow('Control Panel', self.controlPanel, true)
    
    self.inspector = Inspector:create()
    self.mdi:addWindow('Inspector', self.inspector)
    
    self:syncSelection()
    
    self.mdi:loadLayout(layoutPath)    
    self:setModelFile('models/jrpg.c3b')
end

function EffectLab:syncSelection()
    local panels = {self.timeline, self.particlesPanel.list}
    
    function handler(sender, item)
        if item then
            for panel in iter(panels) do
                if panel ~= sender then
                    panel:selectItem(nil)
                end
            end
        end
    end

    for panel in iter(panels) do
        panel.itemSelected:addHandler(handler)
    end
end

function EffectLab:editParticlesConfig(filePath)
    local config = getParticlesConfig(filePath)
    
    self.particlesPanel:addAndSelect(config)
    
end

function EffectLab:onKeyPress(keyCode)
    self.mdi:onKeyPress(keyCode)
end

function EffectLab:update(delta)
    if self.model then
        self.timeline:setAnimate(self.model.curAnimate)
    end
    
    local inspectedOjbect = self.timeline.selectedItem or self.particlesPanel.list.selectedItem
    self.inspector:setObject(inspectedOjbect)
    
    local parameter = nil
    local item = self.inspector.selectedItem
    if item and item.property.className == 'GraphProperty' then
        self.graph:setItem(item)
    else
        self.graph:setItem(nil)
    end
    
    self:inputUpdate(delta)
    
    --[[if self.graph.modified and self.p then
        local times, values = self.graph:getKeyframes()
        self.p:setParameterGraph(2, times, values )
        self.graph.modified = nil
    end]]

end

function EffectLab:isPlaying()
    local animate = self:getCurAnimate()
    return animate and animate:isPlaying()
end

function EffectLab:isLoop()
    local animate = self:getCurAnimate()
    if animate then
        return animate.loop
    else
        return self.controlPanel.loopCheckBox:isSelected()
    end
end

function EffectLab:inputUpdate(delta)
    if not self.model then
        return
    end
    
    local rotationSpeed = math.pi
    local rotation = self.model.rotation or 0

    if theInput.devices[1].values[cc.KeyCode.KEY_LEFT_ARROW] == 1 then
        rotation = rotation + rotationSpeed * delta
    end
    if theInput.devices[1].values[cc.KeyCode.KEY_RIGHT_ARROW] == 1 then
        rotation = rotation - rotationSpeed * delta
    end
    
    self.model.rotation = rotation
    
    local yaw = rotation
    local pitch = 25 / 180 * math.pi
    local quat = yawPitchRoll(yaw, pitch, 0)
    self.model:setRotationQuat(quat)
end

function EffectLab:onMouseWheel(event)
    local value = event:getScrollY()
    
    local factor = self.sheet.scaleFactor 

    factor = factor - value * 0.02
    factor = clamp(factor, 0, 1)
    
    self.sheet.scaleFactor = factor
    
    local k = self.sheet.scaleFactor
    k = k * k
    
    local scale = lerp(0.25, 4, k)   
    self.sheet:setScale(scale)
end

function EffectLab:getCurAnimate()
    return self.model and self.model.curAnimate
end

function EffectLab:setModelFile(filePath)
    local model = Model:create(filePath)
    model:setForceDepthWrite(true)
    
    model:setPosition3D(Vec(0, -100, 0))
    model:setRotation3D(Vec(0, 0, 0))
    
    model:setScale(0.2)
    self:setModel(model)
end

function EffectLab:setModel(model)
    if self.model then
        self.model:removeFromParent()
        self.model = nil
    end
    
    self:addChild(model)
    self.model = model
    
    self.animationListView:setModel(model)
end

function EffectLab:onButtonClick(button)
    
    local name = button:getName()
    
    if name == 'OpenButton' then
        self:openFile()
    elseif name == 'SaveButton' then
        self:saveFile()
    elseif name == 'CloseButton' then
        self.mdi:saveLayout(layoutPath)
        local titleScreen = TitleScreen:create()
        theSceneManager:goTo(titleScreen)
    end
    
end

function EffectLab:openFile()
    theApp.tasks:run(function()
        local dialog = OpenFileDialog:create('models', 'c3b')
        local result = dialog:showAndWait()
        if result then
            self:setModelFile('models/'..result)
        end
    end)
end

function EffectLab:saveFile()   
   serializeToFile(self.model.actionScheme, self.model.actionSchemePath)
end
