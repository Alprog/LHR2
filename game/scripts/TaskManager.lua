
TaskManager = Class('TaskManager')

function TaskManager:init()
    self.tasks = {}
    self.enabled = true
end

function TaskManager:run(func, tag)
    local task = {
        coroutine = coroutine.create(func),
        tag = tag 
    }
    table.insert(self.tasks, task)
    --coroutine.resume(task.coroutine)
end

function TaskManager:update(dt)
    if self.enabled then
        for i = #self.tasks, 1, -1 do
            local task = self.tasks[i]
            
            local status = coroutine.status(task.coroutine)
            if status == 'die' then
                task.stopped = true
            end
            
            if task.stopped then
                table.remove(self.tasks, i)
            else
                deltaTime = dt
                coroutine.resume(task.coroutine)
            end
        end
    end
end

function TaskManager:stopAll()
    for i = 1, #self.tasks do
        self.tasks[i].stopped = true
    end
end

function TaskManager:stopTask(tag)
    for i = 1, #self.tasks do
        local task = self.tasks[i]
        if task.tag == tag then
            task.stopped = true
        end
    end
end
