
--------------------------------
-- @module MeshVertexData
-- @extend Ref
-- @parent_module cc

--------------------------------
--  get attributes count 
-- @function [parent=#MeshVertexData] getMeshVertexAttribCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
-- 
-- @function [parent=#MeshVertexData] getInitialMeshData 
-- @param self
-- @return MeshData#MeshData ret (return value: cc.MeshData)
        
--------------------------------
--  get index data count 
-- @function [parent=#MeshVertexData] getMeshIndexDataCount 
-- @param self
-- @return long#long ret (return value: long)
        
--------------------------------
--  get index data by index 
-- @function [parent=#MeshVertexData] getMeshIndexDataByIndex 
-- @param self
-- @param #int index
-- @return MeshIndexData#MeshIndexData ret (return value: cc.MeshIndexData)
        
--------------------------------
--  get vertexbuffer 
-- @function [parent=#MeshVertexData] getVertexBuffer 
-- @param self
-- @return VertexBuffer#VertexBuffer ret (return value: cc.VertexBuffer)
        
--------------------------------
--  get attribute by index 
-- @function [parent=#MeshVertexData] getMeshVertexAttrib 
-- @param self
-- @param #long index
-- @return MeshVertexAttrib#MeshVertexAttrib ret (return value: cc.MeshVertexAttrib)
        
return nil
