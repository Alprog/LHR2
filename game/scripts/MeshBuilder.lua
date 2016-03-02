
MeshBuilder = Class('MeshBuilder')

-- 3          2  +x           
--  +-------+             
--  |     / |             ^  bitangent (v)
--  |   /   |             |      
--  | /     |             |              
--  +-------+             +-----> tangent (u)
-- 0          1
-- +z

function MeshBuilder:init()
    self:clear()
end

function MeshBuilder:clear()
    self.positions = {}
    self.texs = {}
    self.normals = {}
    self.indices = {}
end

function MeshBuilder:quad(p0, p1, p2, p3)
    local c = #self.positions
    
    local positions = {p0, p1, p2, p3}
    table.insertRange(self.positions, positions)    
   
    local normal = Vector.getNormalized((p2 - p0) ^ (p3 - p1)) 
    for i = 1, 4 do
        table.insert(self.normals, normal)
    end

    local bitangent = Vector.getNormalized(p3 - p0)
    local tangent = bitangent ^ normal
    
    for p in iter(positions) do
        local u = Vector.dot(p - p0, tangent)
        local v = Vector.dot(p - p0, bitangent)
        table.insert(self.texs, Vec(u, v))
    end
    
    local indices = 
    {    
        0 + c, 1 + c, 2 + c,
        0 + c, 2 + c, 3 + c
    }
    table.insertRange(self.indices, indices)
end

function MeshBuilder:build()
    return createMesh(self)
end