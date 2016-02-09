
require 'Mesh.lua'

Carcase = Derive("Carcase", cc.Sprite3D)

function Carcase:init(name, mesh, material)
    if name then
        mesh = mesh or Carcase:getMesh(name)
        material = material or Carcase:getMaterial(name)
    end
    
    if mesh then
        self:addMesh(mesh:copy())
    end
        
    if material then
        self:setMaterial(material)
    end
end

function Carcase:getMaterial(textureName)
    local cache = theApp.director:getTextureCache()
    local texture = cache:addImage(textureName)
    local program = getShader('default', 'default')
    local state = cc.GLProgramState:create(program)
    state:setUniformTexture('mainTexture', texture)
    return cc.Material:createWithGLStateProgram(state)
end

local mesh = nil

function Carcase:getMesh(name)
    
    if mesh then
        return mesh
    end
    
    local meshData =
    {
        positions = {
            Vector(-0.5, 0, -0.5),
            Vector(0.5, 0, -0.5),
            Vector(0.5, 0, 0.5),
            Vector(-0.5, 0, 0.5)
        },
        texs = {
            Vec(0, 0),
            Vec(0, 1),
            Vec(1, 1),
            Vec(1, 0),
            
            
        },
        indices = {
            0, 1, 2,
            0, 2, 3
        },
        normals = {}
    }
    
    mesh = createMesh(meshData)
    mesh:retain()
    mesh:getMeshIndexData():getMeshVertexData():retain()
    
    return mesh
end
