
--------------------------------
-- @module ParticleSystemNode
-- @extend Node,TextureProtocol
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setTexture 
-- @param self
-- @param #cc.Texture2D texture
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] getTexture 
-- @param self
-- @return Texture2D#Texture2D ret (return value: cc.Texture2D)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] isFull 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] isBlendAdditive 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setBlendAdditive 
-- @param self
-- @param #bool value
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setTotalParticles 
-- @param self
-- @param #int tp
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] getParticleCount 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] getBlendFunc 
-- @param self
-- @return BlendFunc#BlendFunc ret (return value: cc.BlendFunc)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] updateTexCoords 
-- @param self
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- @overload self, int, array_table, array_table, array_table         
-- @overload self, int, array_table, array_table         
-- @overload self, int, array_table, array_table, array_table, array_table         
-- @overload self, int, array_table, array_table, array_table, array_table, array_table         
-- @overload self, int, IParameter         
-- @function [parent=#ParticleSystemNode] setParameterGraph
-- @param self
-- @param #int index
-- @param #array_table times
-- @param #array_table v1
-- @param #array_table v2
-- @param #array_table v3
-- @param #array_table v4
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)

--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] getSettings 
-- @param self
-- @param #float time
-- @return SystemSettings#SystemSettings ret (return value: SystemSettings)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] allocMemory 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] step 
-- @param self
-- @param #float dt
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] reset 
-- @param self
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] initTexCoordsWithRect 
-- @param self
-- @param #rect_table rect
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setTextureWithRect 
-- @param self
-- @param #cc.Texture2D texture
-- @param #rect_table rect
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] initIndices 
-- @param self
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] initWithTotalParticles 
-- @param self
-- @param #int numberOfParticles
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] create 
-- @param self
-- @param #int numberOfParticles
-- @return ParticleSystemNode#ParticleSystemNode ret (return value: cc.ParticleSystemNode)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ParticleSystemNode] setOpacityModifyRGB 
-- @param self
-- @param #bool opacityModifyRGB
-- @return ParticleSystemNode#ParticleSystemNode self (return value: cc.ParticleSystemNode)
        
return nil
