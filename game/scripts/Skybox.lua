
require 'QuadMesh'

Skybox = Class('Skybox', Object)

function Skybox:init()
    
    local points = {
        Vector(-0.5, -0.5, -0.5),
        Vector(0.5, -0.5, -0.5),
        Vector(0.5, 0.5, -0.5),
        Vector(-0.5, 0.5, -0.5),
        Vector(-0.5, -0.5, 0.5),
        Vector(0.5, -0.5, 0.5),
        Vector(0.5, 0.5, 0.5),
        Vector(-0.5, 0.5, 0.5)
    }
    

    self:addSide('back', points, 1, 2, 3, 4)
    self:addSide('right', points, 2, 6, 7, 3)
    self:addSide('front', points, 6, 5, 8, 7)
    self:addSide('left', points, 5, 1, 4, 8)
    
    self:addSide('up', points, 7, 8, 4, 3)
    self:addSide('down', points, 2, 1, 5, 6)
    
    self:setScale(100)
end

function Skybox:addSide(name, p, i1, i2, i3, i4)
    local builder = MeshBuilder:create()
    builder:addQuad(p[i1], p[i2], p[i3], p[i4])
    local mesh = builder:build()
        
    local state = createState('skybox', 'skyboxMRT')
    state:setUniformTexture('mainTexture', getTexture('skybox/'.. name ..'.png'))
    local material = cc.Material:createWithGLStateProgram(state)
    material:getStateBlock():setCullFace(true)
    mesh:setMaterial(material)
    
    local sprite = cc.Sprite3D:create()
    sprite:addMesh(mesh)
    
    sprite:setCameraMask(cc.CameraFlag.Skybox)
    self:addChild(sprite)
end