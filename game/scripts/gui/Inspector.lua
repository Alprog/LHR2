
Inspector = Derive('Inspector', ListView)

function Inspector:init()
    Inspector.base.init(self)
    self.rowHeight = 15
end

function Inspector:createView()
    return PropertyView:create()
end

function Inspector:setObject(object)
    if self.object ~= object then
        self.object = object
    
        local items = {}
        
        if object then
            local properties = object:getProperties()
            for i = 1, #properties do
                local pair = {
                    object = object,
                    property = properties[i]
                }
                table.insert(items, pair)
            end
        end
        
        self:setItems(items)
    end
end