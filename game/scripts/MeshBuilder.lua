
MeshBuilder = Class('MeshBuilder')

function MeshBuilder:init()
    self.positions = {}
    self.texs = {}
    self.normals = {}
    self.indices = {}
end


local ccwTexs = { Vec(0, 1), Vec(1, 1), Vec(0, 0), Vec(1, 0) }

function MeshBuilder:quad(v0, v1, v2, v3)
    table.insertRange(self.positions, {v0, v1, v2, v3})    
    table.insertRange(self.texs, ccwTexs)
    
    local normal = (v2 - v1) ^ (v3 - v0)
    
    for i = 1, 4 do
        table.insert(self.normals, normal)
    end

    local c = #self.indices
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