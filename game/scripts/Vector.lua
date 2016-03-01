
Vector = Class('Vector')

function Vector:init(x, y, z)
    self.x = x or 0
    self.y = y or 0
    self.z = z or 0
end

function Vector:__add(v)
    return Vector(
        self.x + v.x,
        self.y + v.y,
        self.z + v.z
    )
end

function Vector:__sub(v)
    return Vector(
        self.x - v.x,
        self.y - v.y,
        self.z - v.z
    )
end

function Vector:__mul(v)
    if type(v) == 'number' then
        return Vector(self.x * v, self.y * v, self.z * v)
    else
        return Vector(
            self.x * v.x,
            self.y * v.y,
            self.z * v.z
        )
    end
end

function Vector:__div(v)
    if type(v) == 'number' then
        return Vector(self.x / v, self.y / v, self.z / v)
    else
        return Vector(
            self.x / v.x,
            self.y / v.y,
            self.z / v.z
        )
    end
end

function Vector:__pow(v)
    return Vector.cross(self, v)
end

function Vector.cross(a, b)
    return Vector(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    )
end

function Vector.dot(a, b)
    return a.x * b.x + a.y * b.y + a.z * b.z
end

function Vector:copy()
    return Vector(self.x, self.y, self.z)
end

function Vector:length()
    return math.sqrt(self.x * self.x + self.y * self.y + self.z * self.z)
end

function Vector:normalize()
    local len = self:length()
    if len > 0 then
        self.x = self.x / len
        self.y = self.y / len
        self.z = self.z / len
    end
end

function Vector:getNormalized()
    local len = self:length()
    if len == 0 then 
        len = 1
    end
    return Vector(
        self.x / len,
        self.y / len,
        self.z / len
    )    
end