
SceneManager = Class('SceneManager')

local virtualHeight = 768

function SceneManager:init(app)
    self.app = app
    self.scenes = {}
    self.root = cc.Node:create()
    self:onResize(app.windowSize)
end

function SceneManager:getTopScene()
    return self.scenes[#self.scenes]
end

function SceneManager:_killTopScene()
    local scene = self:getTopScene()
    if scene then
        scene:onExit()
        scene:destroy()
        scene:removeFromParent()
        self.scenes[#self.scenes] = nil
    end
end

function SceneManager:_addScene(scene)
    table.insert(self.scenes, scene)
    scene:onResize(self.app.windowSize)
    self.root:addChild(scene)
    scene:onEnter()
end

function SceneManager:goTo(scene)
    self:_killTopScene()
    self:_addScene(scene)
end

function SceneManager:push(scene)
    local topScene = self:getTopScene()
    if topScene then
        topScene:onExit()
    end
    self:_addScene(scene)
end

function SceneManager:pop()
    if #self.scenes > 0 then
        self:_killTopScene()
        local topScene = self:getTopScene()
        if topScene then
            topScene:onEnter()
        end
    end
end

function SceneManager:refreshSize()
    self:onResize(self.app.windowSize)
end

function SceneManager:onResize(size)
    local scale = size.height / virtualHeight
    self.root:setScale(scale)
    self.root:setPosition(Vec(size.width / 2, size.height / 2))
    
    for i = 1, #self.scenes do
        self.scenes[i]:onResize(size)
    end
end

function SceneManager:onKeyPress(keyCode)
    local topScene = self:getTopScene()
    if topScene then
        if topScene.onKeyPress then
            topScene:onKeyPress(keyCode)
        end
    end
end

function SceneManager:render()
    
end
