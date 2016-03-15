
--------------------------------
-- @module Camera
-- @extend Node
-- @parent_module cc

--------------------------------
-- get view projection matrix
-- @function [parent=#Camera] getViewProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- 
-- @function [parent=#Camera] render 
-- @param self
-- @param #cc.Node scene
-- @param #int flag
-- @param #int techniqueIndex
-- @param #cc.experimental::FrameBuffer frameBuffer
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] applyViewport 
-- @param self
-- @param #cc.experimental::FrameBuffer frameBuffer
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- set the background brush. See CameraBackgroundBrush for more information.<br>
-- param clearBrush Brush used to clear the background
-- @function [parent=#Camera] setBackgroundBrush 
-- @param self
-- @param #cc.CameraBackgroundBrush clearBrush
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Make Camera looks at target<br>
-- param target The target camera is point at<br>
-- param up The up vector, usually it's Y axis
-- @function [parent=#Camera] lookAt 
-- @param self
-- @param #vec3_table target
-- @param #vec3_table up
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Get clear brush
-- @function [parent=#Camera] getBackgroundBrush 
-- @param self
-- @return CameraBackgroundBrush#CameraBackgroundBrush ret (return value: cc.CameraBackgroundBrush)
        
--------------------------------
-- 
-- @function [parent=#Camera] setPerspective 
-- @param self
-- @param #float fieldOfView
-- @param #float aspectRatio
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Gets the camera's projection matrix.<br>
-- return The camera projection matrix.
-- @function [parent=#Camera] getProjectionMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Get object depth towards camera
-- @function [parent=#Camera] getDepthInView 
-- @param self
-- @param #mat4_table transform
-- @return float#float ret (return value: float)
        
--------------------------------
-- Before rendering scene with this camera, the background need to be cleared. It clears the depth buffer with max depth by default. Use setBackgroundBrush to modify the default behavior
-- @function [parent=#Camera] clearBackground 
-- @param self
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- @overload self, cc.experimental::Viewport         
-- @overload self, float, float, float, float         
-- @function [parent=#Camera] setViewport
-- @param self
-- @param #float left
-- @param #float bottom
-- @param #float width
-- @param #float height
-- @return Camera#Camera self (return value: cc.Camera)

--------------------------------
--  init camera 
-- @function [parent=#Camera] initDefault 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Camera] applyScissors 
-- @param self
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Gets the type of camera.<br>
-- return The camera type.
-- @function [parent=#Camera] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Camera] initOrthographic 
-- @param self
-- @param #float left
-- @param #float right
-- @param #float bottom
-- @param #float top
-- @param #float nearPlane
-- @param #float farPlane
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Is this aabb visible in frustum
-- @function [parent=#Camera] isVisibleInFrustum 
-- @param self
-- @param #cc.AABB aabb
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set additional matrix for the projection matrix, it multiplys mat to projection matrix when called, used by WP8
-- @function [parent=#Camera] setAdditionalProjection 
-- @param self
-- @param #mat4_table mat
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] projectGL 
-- @param self
-- @param #vec3_table src
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Gets the camera's view matrix.<br>
-- return The camera view matrix.
-- @function [parent=#Camera] getViewMatrix 
-- @param self
-- @return mat4_table#mat4_table ret (return value: mat4_table)
        
--------------------------------
-- Get the frustum's near plane.
-- @function [parent=#Camera] getNearPlane 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Camera] project 
-- @param self
-- @param #vec3_table src
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#Camera] getEyePosition 
-- @param self
-- @return vec3_table#vec3_table ret (return value: vec3_table)
        
--------------------------------
-- 
-- @function [parent=#Camera] setOrthographic 
-- @param self
-- @param #float left
-- @param #float right
-- @param #float bottom
-- @param #float top
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Get the frustum's far plane.
-- @function [parent=#Camera] getFarPlane 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Set Scissors for camera.
-- @function [parent=#Camera] setScissors 
-- @param self
-- @param #rect_table rect
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Whether or not the viewprojection matrix was updated since the last frame.<br>
-- return True if the viewprojection matrix was updated since the last frame.
-- @function [parent=#Camera] isViewProjectionUpdated 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Camera] initPerspective 
-- @param self
-- @param #float fieldOfView
-- @param #float aspectRatio
-- @param #float nearPlane
-- @param #float farPlane
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates an orthographic camera.<br>
-- param zoomX The zoom factor along the X-axis of the orthographic projection (the width of the ortho projection).<br>
-- param zoomY The zoom factor along the Y-axis of the orthographic projection (the height of the ortho projection).<br>
-- param nearPlane The near plane distance.<br>
-- param farPlane The far plane distance.
-- @function [parent=#Camera] createOrthographic 
-- @param self
-- @param #float left
-- @param #float right
-- @param #float bottom
-- @param #float top
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- Get the visiting camera , the visiting camera shall be set on Scene::render
-- @function [parent=#Camera] getVisitingCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] create 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- Creates a perspective camera.<br>
-- param fieldOfView The field of view for the perspective camera (normally in the range of 40-60 degrees).<br>
-- param aspectRatio The aspect ratio of the camera (normally the width of the viewport divided by the height of the viewport).<br>
-- param nearPlane The near plane distance.<br>
-- param farPlane The far plane distance.
-- @function [parent=#Camera] createPerspective 
-- @param self
-- @param #float fieldOfView
-- @param #float aspectRatio
-- @param #float nearPlane
-- @param #float farPlane
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] getDefaultViewport 
-- @param self
-- @return experimental::Viewport#experimental::Viewport ret (return value: cc.experimental::Viewport)
        
--------------------------------
-- 
-- @function [parent=#Camera] setDefaultViewport 
-- @param self
-- @param #cc.experimental::Viewport vp
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- Get the default camera of the current running scene.
-- @function [parent=#Camera] getDefaultCamera 
-- @param self
-- @return Camera#Camera ret (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] visit 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table parentTransform
-- @param #unsigned int parentFlags
-- @return Camera#Camera self (return value: cc.Camera)
        
--------------------------------
-- 
-- @function [parent=#Camera] Camera 
-- @param self
-- @return Camera#Camera self (return value: cc.Camera)
        
return nil
