
local Bits = Class('Bits')

getbits = function(num)
    local bits = {}
    
    local bitValue = 1
    while num ~= 0 do
        if num % (bitValue * 2) == bitValue then
            num = num - bitValue
            table.insert(bits, true)
        else
            table.insert(bits, false)
        end
        bitValue = bitValue * 2
    end
    
    setmetatable(bits, Bits)
    return bits
end

function Bits:tonumber()
    local num = 0
    for i = 1, #self do
        if self[i] then
            num = num + 2 ^ (i - 1)
        end
    end
    return num
end

-- not -
Bits.__unm = function(a)
    local result = {}
    for i = 1, #a do
        result[i] = not a[i]
    end
    setmetatable(result, Bits)
    return result
end

-- and *
Bits.__mul = function(a, b)
    local result = {}
    local count = math.min(#a, #b)
    for i = 1, count do
        result[i] = a[i] and b[i]
    end
    setmetatable(result, Bits)
    return result
end

-- or +
Bits.__add = function(a, b)
    local result = {}
    local count = math.max(#a, #b)
    for i = 1, count do
        result[i] = a[i] or b[i]
    end
    setmetatable(result, Bits)
    return result
end

-- xor ^
Bits.__pow = function(a, b)
    local result = {}
    local count = math.max(#a, #b)
    for i = 1, count do
        result[i] = (a[i] or false) ~= (b[i] or false)
    end
    setmetatable(result, Bits)
    return result
end

-----------------------------------------------------

bitnot = function(a)
    return Bits.tonumber(-getbits(a))
end

bitand = function(a, b)
    return Bits.tonumber(getbits(a) * getbits(b))
end

bitor = function(a, b)
    return Bits.tonumber(getbits(a) + getbits(b))
end

bitxor = function(a, b)
    return Bits.tonumber(getbits(a) ^ getbits(b))
end

-----------------------------------------------------

flags = {}

flags.contain = function(flags, flag)
    return bitand(flags, flag) == flag
end

flags.add = function(flags, flag)
    return bitor(flags, flag)
end

flags.remove = function(flags, flag)
    return Bits.tonumber(getbits(flags) * -getbits(flag))
end
