
require 'Mesh.lua'

Carcase = Derive("Carcase", cc.Sprite3D)

function Carcase:init(name, mesh, material)
    if name then
        mesh = mesh or Carcase:getMesh(name)
    end
    
    if mesh then
        self:addMesh(mesh:copy())
    end
        
    if material then
        self:setMaterial(material)
    end
    
    self:setForceDepthWrite(true)
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
            Vector(-0.5, 0, 0.5),
            Vector(-0.5, -1, -0.5),
            Vector(-0.5, -1, 0.5),
            Vector(-0.5, -1, 0.5),
            Vector(0.5, -1, 0.5)
        },
        texs = {
            Vec(0, 0),
            Vec(0, 1),
            Vec(1, 1),
            Vec(1, 0),
            Vec(0, 1),
            Vec(1, 1),
            Vec(0, 0),
            Vec(0, 0)
        },
        indices = {
            0, 1, 2,
            0, 2, 3,
            0, 3, 4,
            3, 4, 5,
            3, 2, 6,
            2, 6, 7
        },
        normals = 
        {
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(-1, 0, 0),
            Vector(-1, 0, 0),
            Vector(0, 0, 1),
            Vector(0, 0, 1),
        }
    }
    
    mesh = createMesh(meshData)
    mesh:retain()
    mesh:getMeshIndexData():getMeshVertexData():retain()
    
    return mesh
end
