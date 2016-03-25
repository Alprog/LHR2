
local quadMesh = nil

function getQuadMesh()
    if not quadMesh then
        local builder = MeshBuilder:create()
        builder:addQuad(Vector(0, 0, 0), Vector(1, 0, 0), Vector(1, 1, 0), Vector(0, 1, 0))
        quadMesh = builder:build()
        quadMesh:retain()
    end
    return quadMesh:copy()
end