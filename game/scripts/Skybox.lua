
require 'QuadMesh'

Skybox = Class('Skybox', Object)

function Skybox:init()
    
    local builder = MeshBuilder:create()
    builder:addQuad(Vector(-0.5, -0.5, -0.5), Vector(0.5, -0.5, -0.5), Vector(0.5, 0.5, -0.5), Vector(-0.5, 0.5, -0.5))
    local mesh = builder:build()
    mesh:calculateAABB()
        
    local state = createState('skybox', 'defaultMRT')
    state:setUniformTexture('mainTexture', getTexture('skybox/back.png'))
    local material = cc.Material:createWithGLStateProgram(state)
    material:getStateBlock():setDepthTest(true)
    material:getStateBlock():setCullFace(true)
    mesh:setMaterial(material)
    
    local sprite = cc.Sprite3D:create()
    sprite:addMesh(mesh)
    
    sprite:setCameraMask(cc.CameraFlag.Skybox)
    
    
    print(dump(sprite:getContentSize()))
    
    self:addChild(sprite)
end

function Skybox:addSection(name)
    
end