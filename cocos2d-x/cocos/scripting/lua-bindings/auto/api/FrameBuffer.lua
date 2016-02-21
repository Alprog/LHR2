
--------------------------------
-- @module FrameBuffer
-- @extend Ref
-- @parent_module ccexp

--------------------------------
-- 
-- @function [parent=#FrameBuffer] getFID 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getTexel 
-- @param self
-- @param #int x
-- @param #int y
-- @return vec4_table#vec4_table ret (return value: vec4_table)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getWidth 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] initWithGLView 
-- @param self
-- @param #cc.GLView view
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getDepthStencilTarget 
-- @param self
-- @return experimental::RenderTargetDepthStencil#experimental::RenderTargetDepthStencil ret (return value: cc.experimental::RenderTargetDepthStencil)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getClearDepth 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getClearStencil 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] applyFBO 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] setClearStencil 
-- @param self
-- @param #char stencil
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getRenderTarget 
-- @param self
-- @return experimental::RenderTargetBase#experimental::RenderTargetBase ret (return value: cc.experimental::RenderTargetBase)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getHeight 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] clearFBO 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] init 
-- @param self
-- @param #unsigned char fid
-- @param #unsigned int width
-- @param #unsigned int height
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] isDefaultFBO 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] setClearColor 
-- @param self
-- @param #color4f_table color
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getFBO 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getClearColor 
-- @param self
-- @return color4f_table#color4f_table ret (return value: color4f_table)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] attachRenderTarget 
-- @param self
-- @param #cc.experimental::RenderTargetBase rt
-- @param #int inde
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] attachDepthStencilTarget 
-- @param self
-- @param #cc.experimental::RenderTargetDepthStencil rt
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] newImage 
-- @param self
-- @param #bool fliimage
-- @return Image#Image ret (return value: cc.Image)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] setClearDepth 
-- @param self
-- @param #float depth
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] setSize 
-- @param self
-- @param #int width
-- @param #int height
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getOrCreateDefaultFBO 
-- @param self
-- @param #cc.GLView glView
-- @return experimental::FrameBuffer#experimental::FrameBuffer ret (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] create 
-- @param self
-- @param #unsigned char fid
-- @param #unsigned int width
-- @param #unsigned int height
-- @return experimental::FrameBuffer#experimental::FrameBuffer ret (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] applyDefaultFBO 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] clearAllFBOs 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] getDefaultFBO 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer ret (return value: cc.experimental::FrameBuffer)
        
--------------------------------
-- 
-- @function [parent=#FrameBuffer] FrameBuffer 
-- @param self
-- @return experimental::FrameBuffer#experimental::FrameBuffer self (return value: cc.experimental::FrameBuffer)
        
return nil
