
MeshBuilder = Class('MeshBuilder')

-- 0          1  +x           
--  +-------+             
--  |     / |             ^  
--  |   /   |             |   bitangent (v-coordinate)   
--  | /     |             |              
--  +-------+             |        
-- 2          3
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

local ccwTexs = { Vec(0, 1), Vec(1, 1), Vec(0, 0), Vec(1, 0) }

function MeshBuilder:quad(p0, p1, p2, p3)
    local c = #self.positions
    
    local positions = {p0, p1, p2, p3}
    table.insertRange(self.positions, positions)    
   
    local normal = Vector.getNormalized((p2 - p1) ^ (p3 - p0)) 
    for i = 1, 4 do
        table.insert(self.normals, normal)
    end

    local bitangent = Vector.getNormalized(p0 - p2)
    local tangent = bitangent ^ normal
    
    for p in iter(positions) do
        local u = Vector.dot(p - p2, tangent)
        local v = Vector.dot(p - p2, bitangent)
        table.insert(self.texs, Vec(u, v))
    end
    
    local indices = 
    {    
        0 + c, 2 + c, 1 + c,
        1 + c, 2 + c, 3 + c
    }
    table.insertRange(self.indices, indices)
end

function MeshBuilder:build()
    return createMesh(self)
end