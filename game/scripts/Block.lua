
require 'MeshBuilder.lua'

Block = Class('Block', Object)

function Block:init()
    Object.init(self)
    
    self.heights = { [0] = 0, 0, 0, 0 }
    self.rotation = 0
    
    self.textureNames = { 'tiles/grass.png', 'tiles/soil.png' }
    self:reloadGfx()
end

function Block:reloadGfx()
    if self.gfx then
        self.gfx:removeFromParent()
        self.gfx = nil
    end
    self:initGfx()
end

function Block:initGfx()

    self.gfx = Carcase:create()
    
    self.gfx = cc.Sprite3D:create()
    
    local meshes = self:getMeshes()
    
    for i = 1, #meshes do
        local mesh = meshes[i]
        local state = createState('default3d', 'blockMRT')
        state:setUniformTexture('mainTexture', getTexture(self.textureNames[i]))
        state:setUniformVec2('u_id', self:getUniformId())
        
        local material = cc.Material:createWithGLStateProgram(state)
        mesh:setMaterial(material)
    
        self.gfx:addMesh(mesh)
    end

    self.gfx:setCullFaceEnabled(true)
    
    self:addChild(self.gfx)
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

function Block:getMeshes()
    local meshes = {}
        
    local meshBuilder = MeshBuilder:create()   
    local s = Vector(0, 0.25, 0)
    
    local p = self:getCorners()
    
    local delta = (p[0].y + p[2].y) - (p[1].y + p[3].y)
    if delta == 0 then
        meshBuilder:addQuad(p[0], p[1], p[2], p[3])
    else
        if delta > 0 then
            meshBuilder:addTriangle(p[0], p[1], p[2])
            meshBuilder:addTriangle(p[0], p[2], p[3])
        else
            meshBuilder:addTriangle(p[1], p[2], p[3])
            meshBuilder:addTriangle(p[1], p[3], p[0])
        end
    end
        
    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    local up = Vec(0, 1, 0)
    for i = 0, 3 do
        local j = (i + 1) % 4
        meshBuilder:addQuad(p[i] - s, p[j] - s, p[j], p[i], up)
    end

    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    return meshes
end

function Block:onHover(value)
    if value == false then
        self:setEntireHighlight(false)
        self:setPartHighlight(false)
    end
end

function Block:skew(value)
    self.offset = self.offset + value / 4
    self:reloadGfx()
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
    
    self:reloadGfx()
end

function Block:changeHeight(index, value)
    self.heights[index] = self.heights[index] + value
end

function Block:rotate()
    self.rotation = (self.rotation + 90) % 360
    self:setRotation3D(Vec(0, self.rotation, 0))
end

function Block:setHighlight(allowCorners, allowSides, affectNeighbors, camera)
    self:setEntireHighlight(true)
    self.affectNeighbors = affectNeighbors
    
    local partHighlight = allowCorners or allowSides
    if not partHighlight then
        self:setPartHighlight(false)
        return
    end
    
    local x = Input.mousePos.x / theApp.windowSize.width * 2 - 1
    local y = Input.mousePos.y / theApp.windowSize.height * 2 - 1
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
            local mesh = child:getMeshByIndex(i)
            local state = mesh:getGLProgramState()
            local color = value and Vec(0.25, 0.25, 0.25) or Vec(0, 0, 0)
            state:setUniformVec3('u_addColor', color)
        end
    end
end

function Block:setPartHighlight(type)
    local state = self.gfx:getMeshByIndex(0):getGLProgramState()
    local texture = type and getTexture('editor/highlight/'..type..'.png') or 0
    state:setUniformTexture('cornerTexture', texture)
    self.cornerType = type
end
