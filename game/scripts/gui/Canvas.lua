
Canvas = Derive('Canvas', cc.Node)

function Canvas:drawLineStrip(points, color, thickness)
    for i = 1, #points - 1 do
        self:drawLine(points[i], points[i + 1], color, thickness)
    end
end

function Canvas:addSprite(color)
    local sprite = cc.Sprite:create('pixel.png')
    self:addChild(sprite)
    sprite:setColor(color or cc.WHITE)
    return sprite
end

function Canvas:drawLine(p1, p2, color, thickness)
    local sprite = self:addSprite(color)
    
    local diff = p2 - p1
    local length = diff:length()
    local angle = math.atan2(diff.y, diff.x)
    
    sprite:setAnchorPoint(0, 0.5)
    sprite:setPosition(p1.x, p1.y)
    sprite:setScale(length, thickness or 1)
    sprite:setRotation(-angle / math.pi * 180)
end

function Canvas:drawSquare(point, size, color)
    local sprite = self:addSprite(color)
    sprite:setPosition(point.x, point.y)
    sprite:setScale(size, size)
end

function Canvas:clear()
    self:removeAllChildren()
end