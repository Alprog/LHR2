
AnimationListView = Derive('AnimationListView', ListView)

function AnimationListView:instantinate()
    return AnimationListView.__create()
end

function AnimationListView:init(scene)
    self.base.init(self)
    self.scene = scene
end

function AnimationListView:setModel(model)
    if self.model ~= model then
        print(self.model)
        self.model = model
        local names = {}
        for k, v in pairs(model.animations) do
            table.insert(names, k)
        end
        self:setItems(names)
        if #names then
            self:selectIndex(1)
        end
    end
end

function AnimationListView:onSelectItem(item)
    if self.model and item then
        local isPlaying = self.scene:isPlaying()
        local isLoop = self.scene:isLoop()
        self.model:clearEffects()
        self.model:play(item, isLoop, isPlaying and 1 or 0)
    end
end