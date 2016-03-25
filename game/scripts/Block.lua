
require 'MeshBuilder.lua'

Block = Class('Block', Object)
Block.serializableFields = { 'heights', 'textureNames' }

-- 3          2  +x           
--  +-------+             
--  |     / |             ^  bitangent (v)
--  |   /   |             |      
--  | /     |             |              
--  +-------+             +-----> tangent (u)
-- 0          1
-- +z

local defaultUV = { Vec(0, 0), Vec(1, 0), Vec(1, 1), Vec(0, 1) }
local oppositeIndexes = { {3, 2}, {0, 3}, {1, 0}, {2, 1} }

function Block:init(section, floor)
    Block.base.init(self)
    
    self.section = section
    self.floor = floor
    section:addChild(self)
    
    self.heights = { [0] = 0, 0, 0, 0 }
    self.textureNames = { 'tiles/grass', 'tiles/rock' }
    
    self.scale = 0.05
end

function Block:onDeserialize()
    Block.base.init(self)
    self.scale = 0.05
end

function Block:getSection()
   return self:getParent() 
end

function Block:recreateGfx()
    if self.gfx then
        self.gfx:removeFromParent()
        self.gfx = nil
    end
    self:initGfx()
end

function Block:changeTexture()
    self.textureNames[1] = 'tiles/brickwall'
    self:recreateGfx()
end

function Block:initGfx()
    if self.gfx ~= nil then
        return
    end

    self.gfx = cc.Sprite3D:create()
    
    local meshes = self:createMeshes()
    
    for i = 1, #meshes do
        local mesh = meshes[i]
        local material = cc.Material:create()
        
        local state = createState('default3d', 'blockMRT')
        local mainTexture = getTexture(self.textureNames[i] .. '.png')
        local normalTexure = getTexture(self.textureNames[i] .. '_n.png')
        state:setUniformTexture('mainTexture', mainTexture)
        if normalTexure then
            state:setUniformTexture('normalTexture', normalTexure)
        end
        state:setUniformVec2('u_id', self:getUniformId())
        local technique = cc.Technique:createWithGLProgramState(state)
        technique:getStateBlock():setCullFaceSide(GL_BACK)
        technique:getStateBlock():setCullFace(true)
        material:setTechnique(RenderMode.Default, technique)
        
        state = createState('shadowMap', 'shadowMap')
        state:setUniformTexture('normalTexture', normalTexure)
        technique = cc.Technique:createWithGLProgramState(state)
        technique:getStateBlock():setCullFaceSide(GL_BACK)
        technique:getStateBlock():setCullFace(true)
        material:setTechnique(RenderMode.ShadowMap, technique)
        
        
        mesh:setMaterial(material)
        self.gfx:addMesh(mesh)
    end

    self.gfx:setCullFaceEnabled(false)

    self:addChild(self.gfx)
    self:addScale(0)
end

function Block:getCorners()
    local p = {
        [0] = Vector(-0.5, self.heights[0], 0.5),
        Vector(0.5, self.heights[1], 0.5),
        Vector(0.5, self.heights[2], -0.5),
        Vector(-0.5, self.heights[3], -0.5)
    }
    return p
end

function Block:createMeshes()
    return 
    {   
        self:createSiteMesh(),
        self:createWallsMesh()
    }
end

function triangleHelper(meshBuilder, p, i1, i2, i3)
    meshBuilder:addTriangle(p[i1], p[i2], p[i3])
    table.insert(meshBuilder.uv1, defaultUV[i1 + 1])
    table.insert(meshBuilder.uv1, defaultUV[i2 + 1])
    table.insert(meshBuilder.uv1, defaultUV[i3 + 1])
end

function Block:createSiteMesh()
    local meshBuilder = MeshBuilder:create() 
    local p = self:getCorners()
       
    local delta = (p[0].y + p[2].y) - (p[1].y + p[3].y)
    if delta == 0 then
        meshBuilder:addQuad(p[0], p[1], p[2], p[3])
        table.insertRange(meshBuilder.uv1, defaultUV)
    else
        if delta < 0 then
            triangleHelper(meshBuilder, p, 0, 1, 2)
            triangleHelper(meshBuilder, p, 0, 2, 3)
        else
            triangleHelper(meshBuilder, p, 1, 2, 3)
            triangleHelper(meshBuilder, p, 1, 3, 0)
        end
    end
        
    return meshBuilder:build()
end

function Block:getOppositeHeights(side)
    local indexes = oppositeIndexes[side]
    local a, b = indexes[1], indexes[2]
    return self.heights[a], self.heights[b]
end

function Block:createWallsMesh()
    local meshBuilder = MeshBuilder:create() 
    local p = self:getCorners()
    
    local s = Vector(0, 0.25, 0)
    local up = Vec(0, 1, 0)
    
    local neighbors = self:getNeighbors()
    
    for i = 1, 4 do
        local a, b = p[i - 1], p[i % 4]
        local ai, bi
        
        local neighbor = neighbors[i]
        if neighbor then
            local ay, by = neighbor:getOppositeHeights(i)
            ai = Vector(a.x, math.min(a.y, ay), a.z)
            bi = Vector(b.x, math.min(b.y, by), b.z)
        else
            ai = a - s
            bi = b - s
        end
        
        local isA, isB = a.y ~= ai.y, b.y ~= bi.y
        if isA or isB then
            if isA and isB then
                meshBuilder:addQuad(b, a, ai, bi, up)
                table.insertRange(meshBuilder.uv1, defaultUV)
            else
                if isA then
                    meshBuilder:addTriangle(b, a, ai, up)
                else
                    meshBuilder:addTriangle(b, ai, bi, up)
                end
                local zeroUV = {Vec(0, 0), Vec(0, 0), Vec(0, 0)}
                table.insertRange(meshBuilder.uv1, zeroUV)
            end
        end
    end

    if meshBuilder:hasGeometry() then
        return meshBuilder:build()
    end
end

function Block:onHover(value)
    if value == false then
        self:setEntireHighlight(false)
        self:setPartHighlight(false)
    end
end

function Block:extrude(value)
    local index = self.cornerType
    
    if index then
        if index < 4 then
            self:changeHeight(index , value)
        else
            index = index - 4
            self:changeHeight(index, value)
            self:changeHeight((index + 1) % 4, value)
        end
    else
        for i = 0, 3 do
            self:changeHeight(i, value)
        end
    end
    
    self:getSection():getLevel():onReliefChange(self)
end

function Block:changeHeight(index, value)
    self.heights[index] = self.heights[index] + value
end

function Block:setHighlight(allowCorners, allowSides, affectNeighbors, camera)
    self:setEntireHighlight(true)
    self.affectNeighbors = affectNeighbors
    
    local partHighlight = allowCorners or allowSides
    if not partHighlight then
        self:setPartHighlight(false)
        return
    end
    
    local x = theInput.mousePos.x / theApp.windowSize.width * 2 - 1
    local y = theInput.mousePos.y / theApp.windowSize.height * 2 - 1
    local mousePos = Vector(x, y, 0)
    
    local m = self:getNodeToWorldTransform()
    local vp = camera:getViewProjectionMatrix()
    local mvp = cc.mat4.multiply(vp, m)
    local corners = self:getCorners()
    for i = 0, 3 do
        corners[i] = cc.mat4.transformPoint(mvp, corners[i])
        corners[i].z = 0
    end
    
    local points = {}
    if allowCorners then
        for i = 0, 3 do
            points[i] = corners[i]
        end
    end
    
    if allowSides then    
        for i = 0, 3 do
            local j = (i + 1) % 4
            if self.heights[i] == self.heights[j] then
                points[i + 4] = Vector.lerp(corners[i], corners[j], 0.5)
            end
        end
    end

    local index = nil
    local minDist = nil
    for i, point in pairs(points) do
        local dist = (point - mousePos):squaredLength()
        if not minDist or minDist > dist then
            minDist = dist
            index = i            
        end
    end
    
    self:setPartHighlight(index)
end

function Block:setEntireHighlight(value)
    for child in iter(self:getChildren()) do
        local count = child:getMeshCount()
        for i = 0, count - 1 do
            local material = child:getMaterial(i)
            local technique = material:getTechnique(RenderMode.Default)
            local state = technique:getPassByIndex(0):getGLProgramState()
            local color = value and Vec(0.25, 0.25, 0.25) or Vec(0, 0, 0)
            state:setUniformVec3('u_addColor', color)
        end
    end
end

function Block:setPartHighlight(type)
    local technique = self.gfx:getMaterial(0):getTechnique(RenderMode.Default)
    local state = technique:getPassByIndex(0):getGLProgramState()
    local texture = type and getTexture('editor/highlight/'..type..'.png') or 0
    state:setUniformTexture('highlightTexture', texture)
    self.cornerType = type
end

function Block:addScale(value)
    self.scale = (self.scale or 0) + value
    for child in iter(self:getChildren()) do
        local count = child:getMeshCount()
        for i = 0, count - 1 do
            local mesh = child:getMeshByIndex(i)
            local state = mesh:getGLProgramState()
            state:setUniformFloat('scale', self.scale)
        end
    end
    print(self.scale)
end

function Block:getSection()
    return self:getParent() 
end

function Block:getNeighbors()
    local section = self:getSection()
    return section:getLevel():getNeighbors(section.x, section.z, self.floor)
end

function Block:getHeight(x, z)
    local h = self.heights
    if x + z < 1 then
        return h[3] + (h[2] - h[3]) * x + (h[0] - h[3]) * z
    else
        return h[1] + (h[0] - h[1]) * (1 - x) + (h[2] - h[1]) * (1 - z)        
    end
end