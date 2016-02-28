
Projector = NewClass()

function Projector:init(screen)
    self.screen = screen
    self.sources = {}
end

function Projector:addSource(frameBuffer, index, shaderName)
    local source = 
    {
        frameBuffer = frameBuffer,
        index = index or 1,
        shaderName = shaderName or 'default'
    }
    table.insert(self.sources, source)
end

function Projector:nextSource()
    self.sourceIndex = (self.sourceIndex or 0) + 1
    if self.sourceIndex > #self.sources then
        self.sourceIndex = 1
    end
    self:refreshScreen()
end

function Projector:refreshScreen()
    self.sourceIndex = self.sourceIndex or 1
    local source = self.sources[self.sourceIndex]
    if source then
        
        local texture = source.frameBuffer:getRenderTarget(source.index)
        
        local shader = getShader('sprite', source.shaderName)
        local state = cc.GLProgramState:create(shader)
        state:setUniformTexture('mainTexture', texture)
        self.screen:setGLProgramState(state)
        
        state:setUniformFloat('zNear', 4)
        state:setUniformFloat('zFar', 1000)
    end
end