
require 'MeshBuilder.lua'

Block = Class('Block', Object)

function Block:init()
    Object.init(self)
    
    self.offset = 0
    self.height = 0
    
    self.textureName = 'tiles/soil.png'
    self:reloadGfx()
end

function Block:reloadGfx()
    if self.gfx then
        self.gfx:removeFromParent()
        self.gfx = nil
    end
    self:initGfx()
end

function Block:initGfx()

    self.gfx = Carcase:create()
    
    self.gfx = cc.Sprite3D:create()
    
    local meshes = self:getMeshes()
    
    for mesh in iter(meshes) do
        local state = createState('default3d', 'defaultMRT')
        state:setUniformTexture('mainTexture', getTexture(self.textureName))
        state:setUniformVec2('u_id', self:getUniformId())
        
        local material = cc.Material:createWithGLStateProgram(state)
        mesh:setMaterial(material)
    
        self.gfx:addMesh(mesh)
    end

    self.gfx:setCullFaceEnabled(true)
    
    self:addChild(self.gfx)
    self:updateHighlight()
end

function Block:move(value)
    self.height = self.height + value
    self:setPosition3D(Vec(0, self.height, 0))
end

function Block:getMeshes()
    local meshes = {}
        
    local meshBuilder = MeshBuilder:create()
    
    local v = {}
    v[0] = Vector(-0.5, self.offset, -0.5)
    v[1] = Vector(0.5, 0, -0.5)
    v[2] = Vector(-0.5, self.offset, 0.5)
    v[3] = Vector(0.5, 0, 0.5)
    
    local s = Vector(0, 1, 0)
    
    meshBuilder:quad(v[0], v[1], v[2], v[3])
    
    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    meshBuilder:quad(v[0], v[2], v[0] - s, v[2] - s)
    meshBuilder:quad(v[2], v[3], v[2] - s, v[3] - s)
    meshBuilder:quad(v[3], v[1], v[3] - s, v[1] - s)
    meshBuilder:quad(v[1], v[0], v[1] - s, v[0] - s)
     
    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    return meshes
end

function Block:updateHighlight()
    for child in iter(self:getChildren()) do
        local count = child:getMeshCount()
        for i = 0, count - 1 do
            local mesh = child:getMeshByIndex(i)
            local state = mesh:getGLProgramState()
            local color = self.highlight and Vec(0.5, 0.5, 0.5) or Vec(0, 0, 0)
            state:setUniformVec3('u_addColor', color)
        end
    end
end

function Block:onHover(value)
    self.highlight = value
    self:updateHighlight()
end

function Block:skew(value)
    self.offset = self.offset + value / 4
    self:reloadGfx()
end
