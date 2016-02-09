
Parameter = Class('Parameter')

function Parameter:createDefault()
    return Parameter:create({0}, {1})
end

function Parameter:init(...)
    local components = {...}
    for i = 1, #components do
        self[i] = components[i]
    end
end

function Parameter:getKeyframeCount()
    return #self[1]
end

function Parameter:getKeyframe(index)
    if index >= 1 or index <= #self[1] then
        local keyframe = {}
        for i = 1, #self do
            keyframe[i] = self[i][index]
        end
        return keyframe
    end
end

function Parameter:updateKeyframe(index, keyframe)
    for i = 1, #self do
        self[i][index] = keyframe[i]
    end
end

function Parameter:insertKeyframe(index, keyframe)
    for i = 1, #self do
        table.insert(self[i], index, keyframe[i])
    end
end

function Parameter:pushbackKeyframe(keyframe)
    for i = 1, #self do
        table.insert(self[i], keyframe[i])
    end
end

function Parameter:removeKeyframe(index)
    for i = 1, #self do
        table.remove(self[i], index)
    end
end