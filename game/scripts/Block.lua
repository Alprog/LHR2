
require 'MeshBuilder.lua'

Block = Class('Block', Object)

function Block:init()
    Object.init(self)
    
    self.height = 0
    self.textureName = 'tiles/soil3.png'
    self:initGfx()
end

function Block:initGfx()

    self.gfx = Carcase:create()
    
    self.gfx = cc.Sprite3D:create()
    
    local mesh = self:getMesh()
    
    local state = createState('default3d', 'defaultMRT')
    state:setUniformTexture('mainTexture', getTexture(self.textureName))
    state:setUniformVec2('u_id', self:getUniformId())
    
    local material = cc.Material:createWithGLStateProgram(state)
    mesh:setMaterial(material)
    
    self.gfx:addMesh(mesh)
    self.gfx:setCullFaceEnabled(true)
    
    self:addChild(self.gfx)
end

function Block:move(value)
    self.height = self.height + value
    self.gfx:setPosition3D(Vec(0, self.height, 0))
end

-- 0          1  +x
--  .-------.
--  |     / |
--  |   /   |
--  | /     |
--  .-------.
-- 2          3
-- +z

function Block:getMesh()
    if mesh then
        --return mesh
    end
        
    local meshBuilder = MeshBuilder:create()
    
    meshBuilder:quad(
        Vector(-0.5, 0, -0.5),
        Vector(0.5, 0, -0.5),
        Vector(-0.5, 0, 0.5),
        Vector(0.5, 0, 0.5)
    )
        
    mesh = meshBuilder:build()
    
    --mesh:retain()
    --mesh:getMeshIndexData():getMeshVertexData():retain()
    
    return mesh
end

