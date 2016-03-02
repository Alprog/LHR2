
require 'MeshBuilder.lua'

Block = Class('Block', Object)

function Block:init()
    Object.init(self)
    
    self.offset = 0
    self.height = 0
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
    self:updateHighlight()
end

function Block:getCorners()
    local p = {}
    p[0] = Vector(-0.5, self.offset, 0.5)
    p[1] = Vector(0.5, self.offset, 0.5)
    p[2] = Vector(0.5, 0, -0.5)
    p[3] = Vector(-0.5, 0, -0.5)
    return p
end

function Block:getMeshes()
    local meshes = {}
        
    local meshBuilder = MeshBuilder:create()   
    local s = Vector(0, 0.25, 0)
    
    local p = self:getCorners()
    meshBuilder:quad(p[0], p[1], p[2], p[3])
    
    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    for i = 0, 3 do
        local j = (i + 1) % 4
        meshBuilder:quad(p[i] - s, p[j] - s, p[j], p[i])
    end

    table.insert(meshes, meshBuilder:build())
    meshBuilder:clear()
    
    return meshes
end

function Block:updateHighlight()
    for child in iter(self:getChildren()) do
        local count = child:getMeshCount()
        for i = 0, count - 1 do
            local mesh = child:getMeshByIndex(i)
            local state = mesh:getGLProgramState()
            local color = self.highlight and Vec(0.25, 0.25, 0.25) or Vec(0, 0, 0)
            state:setUniformVec3('u_addColor', color)
        end
    end
end

function Block:onHover(value)
    if value == false then
        self:clearCornerHighlight()
    end
    self.highlight = value
    self:updateHighlight()
end

function Block:skew(value)
    self.offset = self.offset + value / 4
    self:reloadGfx()
end

function Block:move(value)
    self.height = self.height + value
    self:setPosition3D(Vec(0, self.height, 0))
end

function Block:rotate()
    self.rotation = (self.rotation + 90) % 360
    self:setRotation3D(Vec(0, self.rotation, 0))
end

function Block:highlightNearestCorner(camera)
    local x = Input.mousePos.x / theApp.windowSize.width * 2 - 1
    local y = Input.mousePos.y / theApp.windowSize.height * 2 - 1
    local mousePos = Vector(x, y, 0)
    
    local m = self:getNodeToWorldTransform()
    local vp = camera:getViewProjectionMatrix()
    local mvp = cc.mat4.multiply(vp, m)   

    local points = {}
    
    -- corners
    local corners = self:getCorners()
    for i = 0, 3 do
        local p = cc.mat4.transformPoint(mvp, corners[i])
        points[i] = Vector(p.x, p.y, 0)
    end
    
    -- sides
    for i = 0, 3 do
        local sidePoint = Vector.lerp(points[i], points[(i + 1) % 4], 0.5)
        table.insert(points, sidePoint)
    end
    
    local index = nil
    local minDist = nil
    for i = 0, #points do
        local dist = (points[i] - mousePos):squaredLength()
        if not minDist or minDist > dist then
            minDist = dist
            index = i            
        end
    end
    
    self:setCornerHighlightType(index)
end

function Block:clearCornerHighlight()
   self:setCornerHighlightType(nil) 
end

function Block:setCornerHighlightType(index)
    local state = self.gfx:getMeshByIndex(0):getGLProgramState()
    local texture = index and getTexture('editor/highlight/'..index..'.png') or 0
    state:setUniformTexture('addTexture', texture)
end
