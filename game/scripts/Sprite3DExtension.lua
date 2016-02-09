
local Sprite3D = cc.Sprite3D

function Sprite3D:init(name)
end

--[[function Sprite3D:setMesh(mesh)

    if self.mesh then
        error('Sprite3d already has mesh. Mesh replacing is not implement')
    else
        self.mesh = mesh
        self:addMesh(mesh)
    end

end]]