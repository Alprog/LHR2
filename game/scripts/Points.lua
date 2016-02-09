
Points = Class('Points')

function Points:init(value)
    self.cur = value
    self.max = value
end

function Points:restore()
    self.cur = self.max
end

function Points:getPercents()
    return self.cur / self.max * 100
end

function Points:increase(value)
    self.cur = clamp(0, self.cur + value, self.max)
end

function Points:decrease(value)
    self.cur = clamp(0, self.cur - value, self.max)
end

function Points:empty()
    return self.cur <= 0
end