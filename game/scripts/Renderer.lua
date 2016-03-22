
require 'KeepRefFields.lua'
require 'Halton.lua'

Renderer = Class("Renderer")
keepRefFields(Renderer)

function Renderer:init()    
    self.gBuffer = ccexp.FrameBuffer:create(1)       
    self:initShadowMap()
end

function Renderer:initShadowMap()
    local size = cc.size(512, 512)
    self.shadowMapBuffer = ccexp.FrameBuffer:create(1)
    self.shadowMapBuffer:setClearColor(cc.WHITE)
    self.shadowMapBuffer:setSize(size.width, size.height)
    self.shadowMapTexture = self:createTexture(size, cc.DEPTH24_STENCIL8)
    self.auxTexture = self:createTexture(size, cc.RG16F)
    self.auxTexture2 = self:createTexture(size, cc.RG16F)
    self.shadowMapBuffer:attachRenderTarget(0, self.auxTexture)
    self.shadowMapBuffer:attachDepthStencil(self.shadowMapTexture)
end

function Renderer:createTexture(size, format)
    return cc.Texture2D:create(size.width, size.height, format or cc.BGRA8888, 0)
end

function Renderer:onResize(size)
    self.size = size
    self.primaryTexture = self:createTexture(size)
    self.secondaryTexture = self:createTexture(size)
    self.texture3 = self:createTexture(size)
    self.historyTexture = self:createTexture(size)
    
    self.albedoTexture = self:createTexture(size)
    self.normalTexture = self:createTexture(size)
    self.idsTexture = self:createTexture(size)
    self.velocityTexture = self:createTexture(size, cc.RG16F)
    self.depthTexture = self:createTexture(size, cc.DEPTH24_STENCIL8)
    
    self.gBuffer:setSize(size.width, size.height)
    self.gBuffer:attachRenderTarget(0, self.albedoTexture)
    self.gBuffer:attachRenderTarget(1, self.normalTexture)
    self.gBuffer:attachRenderTarget(2, self.idsTexture)
    self.gBuffer:attachRenderTarget(3, self.velocityTexture)
    self.gBuffer:attachDepthStencil(self.depthTexture)
    
    self.rsMaterial = nil
    self.vbMaterial = nil
    self.hbMaterial = nil
    self.lMaterial = nil
    self.aaMaterial = nil
end

function Renderer:render(scene)
    self.scene = scene
    
    self:reprojectCamera()
    
    self:renderGeometry()
    self:bakeShadows()
    self:lighting()
    self:renderTranparent()
    
    self:temporalAA()
    self:swapFields('primaryTexture', 'historyTexture')
end

function Renderer:reprojectCamera()
    self.frame = (self.frame or 0) + 1
    if self.frame > #Halton then
        self.frame = 1
    end
    self.prevOffset = self.offset and self.offset:copy() or Vector(0, 0)
    
    local sample = Halton[self.frame]
    local x = (sample.x - 0.5) / self.size.width * 2
    local y = (sample.y - 0.5) / self.size.height * 2
    self.offset = Vector(x, y)
    
    self.scene.camera:setOffset(self.offset)
end

function Renderer:renderGeometry()
    self.gBuffer:clearFBO()
    self.scene.camera:render(self.scene, cc.CameraFlag.DEFAULT, RenderMode.Default, self.gBuffer)
end

function Renderer:bakeShadows()
    self:renderShadowMap()
    self:blur(self.auxTexture, self.auxTexture2)
    self:renderScreenShadow()
end

function Renderer:renderShadowMap()
    self.shadowMapBuffer:clearFBO()
    self.scene.lightCamera:render(self.scene, cc.CameraFlag.DEFAULT, RenderMode.ShadowMap, self.shadowMapBuffer)
end

function Renderer:blur(texture, tmpTexture)
    texture = texture or self.primaryTexture
    tmpTexture = tmpTexture or self.secondaryTexture
    
    if not self.vbMaterial then
        self.vbMaterial = createMaterial('vblur', 'blur')
    end
    self.vbMaterial.state:setUniformTexture('mainTexture', texture)
    thePostProcessor:perform(self.vbMaterial, tmpTexture)
    
    if not self.hbMaterial then
        self.hbMaterial = createMaterial('hblur', 'blur')
    end
    self.hbMaterial.state:setUniformTexture('mainTexture', tmpTexture)
    thePostProcessor:perform(self.hbMaterial, texture)
end

function Renderer:renderScreenShadow()
    
    local material = self.rsMaterial
    if not material then
        material = createMaterial('post', 'shadow')
        material.state:setUniformTexture('depthTexture', self.depthTexture)
        material.state:setUniformTexture('normalTexture', self.normalTexture)
        material.state:setUniformTexture('shadowMapTexture', self.auxTexture)
        self.rsMaterial = material
    end

    local screenToWorld = cc.mat4.getInversed(self.scene.camera:getViewProjectionMatrix())
    material.state:setUniformMat4('screenToWorld', screenToWorld)
    material.state:setUniformMat4('worldToShadowMap', self.scene.lightCamera:getViewProjectionMatrix())
    local position = self.scene.lightCamera:getPosition3D()  
    material.state:setUniformVec3('lightPosition', position)
    
    thePostProcessor:perform(material, self.primaryTexture)
end

function Renderer:swapFields(a, b)
    local map = rawget(self, 'map')
    map[a], map[b] = map[b], map[a]
end

function Renderer:swapTextures()
    self:swapFields('primaryTexture', 'secondaryTexture')
end

function Renderer:lighting() 
    self:swapTextures()
    
    local material = self.lMaterial
    if not material then
        material = createMaterial('post', 'halflambert')
        material.state:setUniformTexture('albedoTexture', self.albedoTexture)
        material.state:setUniformTexture('normalTexture', self.normalTexture)
        material.state:setUniformTexture('normalTexture2', self.idsTexture)
        material.state:setUniformTexture('wrapTexture', getTexture('wrap2.png'))
        self.lMaterial = material
    end
    
    material.state:setUniformTexture('shadowTexture', self.secondaryTexture)

    local m = self.scene.lightCamera:getNodeToWorldTransform()
    local dir = cc.mat4.transformVector(m, Vector(0, 0, 1))
    material.state:setUniformVec3('lightDir', dir)

    thePostProcessor:perform(material, self.primaryTexture)
end

function Renderer:renderTranparent()
    
end

function Renderer:temporalAA()
    self:swapTextures()
    
    local material = self.aaMaterial
    if not material then
        material = createMaterial('post', 'temporalAA')
        self.aaMaterial = material
    end
    material.state:setUniformTexture('mainTexture', self.secondaryTexture)
    material.state:setUniformTexture('historyTexture', self.historyTexture)
    material.state:setUniformTexture('velocityTexture', self.velocityTexture)
    material.state:setUniformVec2('veloOffset', self.offset - self.prevOffset)
        
    thePostProcessor:perform(material, self.primaryTexture)
end

function Renderer:getObjectFromScreenPos(pos)
    local texel = self.gBuffer:getTexel(GBuffer.Index.Ids, pos.x, pos.y)
    local index = bytesToIndex(texel.x, texel.y)
    return Object:fromIndex(index)
end