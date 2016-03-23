
Cell = Derive('Cell', Object)

function Cell:init()
    Cell.base.init(self)
    
 
    local textureName = 'tiles/soil2.png'

    self.gfx = Carcase:create(textureName, nil, self:getMaterial(textureName))
    
    local selection = Carcase:create('tiles/select.png', nil, self:getMaterial('tiles/select.png'))
    selection:setVisible(false)
    selection:setPosition3D(Vec(0, 0.01, 0))
    selection:setForceDepthWrite(true)
    self.selection = selection
    
    self:addChild(self.gfx)
    self:addChild(self.selection)
end

function Cell:getMaterial(textureName)
    local texture = getTexture(textureName)
    local state = createState('default3d', 'defaultMRT')
    state:setUniformTexture('mainTexture', texture)
    state:setUniformVec2('u_id', self:getUniformId())
    return cc.Material:createWithGLStateProgram(state)
end