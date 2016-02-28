
--------------------------------
-- @module StateBlock
-- @extend Ref
-- @parent_module cc

--------------------------------
-- Sets the depth function to use when depth testing is enabled.<br>
-- When not explicitly set and when depth testing is enabled, the default<br>
-- depth function is DEPTH_LESS.<br>
-- param func The depth function.
-- @function [parent=#StateBlock] setDepthFunction 
-- @param self
-- @param #int func
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Explicitly sets the source used in the blend function for this render state.<br>
-- Note that the blend function is only applied when blending is enabled.<br>
-- param blend Specifies how the destination blending factors are computed.
-- @function [parent=#StateBlock] setBlendDst 
-- @param self
-- @param #int blend
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Explicitly sets the source used in the blend function for this render state.<br>
-- Note that the blend function is only applied when blending is enabled.<br>
-- param blend Specifies how the source blending factors are computed.
-- @function [parent=#StateBlock] setBlendSrc 
-- @param self
-- @param #int blend
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Explicitly sets the source and destination used in the blend function for this render state.<br>
-- Note that the blend function is only applied when blending is enabled.<br>
-- param blendFunc Specifies how the blending factors are computed.
-- @function [parent=#StateBlock] setBlendFunc 
-- @param self
-- @param #cc.BlendFunc blendFunc
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Binds the state in this StateBlock to the renderer.<br>
-- This method handles both setting and restoring of render states to ensure that<br>
-- only the state explicitly defined by this StateBlock is applied to the renderer.
-- @function [parent=#StateBlock] bind 
-- @param self
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Toggles depth testing.<br>
-- By default, depth testing is disabled.<br>
-- param enabled true to enable, false to disable.
-- @function [parent=#StateBlock] setDepthTest 
-- @param self
-- @param #bool enabled
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Sets the side of the facets to cull.<br>
-- When not explicitly set, the default is to cull back-facing facets.<br>
-- param side The side to cull.
-- @function [parent=#StateBlock] setCullFaceSide 
-- @param self
-- @param #int side
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- 
-- @function [parent=#StateBlock] isDirty 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Toggles blending.<br>
-- param enabled true to enable, false to disable.
-- @function [parent=#StateBlock] setBlend 
-- @param self
-- @param #bool enabled
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- 
-- @function [parent=#StateBlock] getHash 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Explicitly enables or disables backface culling.<br>
-- param enabled true to enable, false to disable.
-- @function [parent=#StateBlock] setCullFace 
-- @param self
-- @param #bool enabled
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Sets the winding for front facing polygons.<br>
-- By default, counter-clockwise wound polygons are considered front facing.<br>
-- param winding The winding for front facing polygons.
-- @function [parent=#StateBlock] setFrontFace 
-- @param self
-- @param #int winding
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Toggles depth writing.<br>
-- param enabled true to enable, false to disable.
-- @function [parent=#StateBlock] setDepthWrite 
-- @param self
-- @param #bool enabled
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Sets a render state from the given name and value strings.<br>
-- This method attempts to interpret the passed in strings as render state<br>
-- name and value. This is normally used when loading render states from<br>
-- material files.<br>
-- param name Name of the render state to set.<br>
-- param value Value of the specified render state.
-- @function [parent=#StateBlock] setState 
-- @param self
-- @param #string name
-- @param #string value
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Invalidates the default StateBlock.<br>
-- Only call it if you are calling GL calls directly. Invoke this function<br>
-- at the end of your custom draw call.<br>
-- This function restores the default render state its defaults values.<br>
-- Since this function might call GL calls, it must be called in a GL context is present.<br>
-- param stateBits Bitwise-OR of the states that needs to be invalidated
-- @function [parent=#StateBlock] invalidate 
-- @param self
-- @param #long stateBits
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
-- Creates a new StateBlock with default render state settings.
-- @function [parent=#StateBlock] create 
-- @param self
-- @return StateBlock#StateBlock ret (return value: cc.StateBlock)
        
--------------------------------
-- Restores the global Render State to the default state<br>
-- The difference between `invalidate()` and `restore()`, is that `restore()` will<br>
-- restore the global Render State based on its current state. Only the<br>
-- states that were changed will be restored.<br>
-- Rule of thumb:<br>
-- - call `restore()` if you want to restore to the default state after using `StateBlock`.<br>
-- - call `invalidate()` if you want to restore to the default state after calling manual GL calls.
-- @function [parent=#StateBlock] restore 
-- @param self
-- @param #long stateOverrideBits
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
--------------------------------
--  The recommended way to create StateBlocks is by calling `create`.<br>
-- Don't use `new` or `delete` on them.
-- @function [parent=#StateBlock] StateBlock 
-- @param self
-- @return StateBlock#StateBlock self (return value: cc.StateBlock)
        
return nil
