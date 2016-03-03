
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
    self.normals = {}
    self.uv0 = {}
    self.uv1 = {}
    self.uv = self.uv0
    self.indices = {}
end

function MeshBuilder:addQuad(p0, p1, p2, p3, bitangent)
    self:addPolygon(p0, p1, p2, p3, bitangent)
end

function MeshBuilder:addTriangle(p0, p1, p2, bitangent)
    self:addPolygon(p0, p1, p2, nil, bitangent)
end

function MeshBuilder:addPolygon(p0, p1, p2, p3, bitangent)
    local c = #self.positions
    
    local positions = {p0, p1, p2, p3}
    table.insertRange(self.positions, positions)    
   
    local normal = Vector.getNormalized((p2 - p1) ^ (p0 - p1)) 
    for i = 1, #positions do
        table.insert(self.normals, normal)
    end

    bitangent = bitangent or Vector.getNormalized(p2 - p1)
    local tangent = bitangent ^ normal
    
    for p in iter(positions) do
        local u = Vector.dot(p - p0, tangent)
        local v = Vector.dot(p - p0, bitangent)
        table.insert(self.uv, Vec(u, v))
    end
    
    table.insertRange(self.indices, {0 + c, 1 + c, 2 + c})
    if p3 then
        table.insertRange(self.indices, {0 + c, 2 + c, 3 + c})
    end
end

function MeshBuilder:build()
    return createMesh(self)
end