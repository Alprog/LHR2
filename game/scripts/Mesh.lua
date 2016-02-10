
function flat(list)
    local result = {}
    for i = 1, #list do
        local t = list[i]
        table.insert(result, t.x)
        table.insert(result, t.y)
        if t.z then
            table.insert(result, t.z)
        end
        if t.w then
            table.insert(result, t.w)
        end
    end
    return result
end

function cc.Mesh:copy()
    local indexData = self:getMeshIndexData()
    return cc.Mesh:create('', indexData)
end

function combineMesh(infos)
    local meshes = {}
    local data = {}
    
    for info in iter(infos) do
        table.insert(meshes, info.mesh)
        
        local matrix = info.transform
        local index = #data
        for i = 1, #matrix do
            data[index + i] = matrix[i]
        end
        data[#data + 1] = info.texTranslate.x
        data[#data + 1] = info.texTranslate.y
        data[#data + 1] = info.texScale.x
        data[#data + 1] = info.texScale.y   
        data[#data + 1] = info.color.r
        data[#data + 1] = info.color.g
        data[#data + 1] = info.color.b
        data[#data + 1] = info.color.a
    end
    
    return cc.Mesh:combine(meshes, data)
end

function createMesh(meshData)
    local positions = flat(meshData.positions)
    local normals = flat(meshData.normals)
    local texs = flat(meshData.texs)
    return cc.Mesh:create(positions, normals, texs, meshData.indices)
end