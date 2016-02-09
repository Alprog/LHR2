
#include "LinearParameter.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

template <typename T>
LinearParameter<T>::LinearParameter(std::vector<float>& times, std::vector<T>& values)
{
	CC_ASSERT(times.size() == values.size());

	keyframes.resize(times.size());
	for (size_t i = 0; i < times.size(); i++)
	{
		keyframes[i].time = times[i];
		keyframes[i].value = values[i];
	}
}

template <typename T>
T LinearParameter<T>::getValue(float time)
{
	auto& firstKeyframe = keyframes[0];
	if (time <= firstKeyframe.time)
	{
		return firstKeyframe.value;
	}

	for (size_t i = 1; i < keyframes.size(); i++)
	{
		auto& cur = keyframes[i];
		if (time < cur.time)
		{
			auto& prev = keyframes[i - 1];
			auto k = (time - prev.time) / (cur.time - prev.time);
			return prev.value + (cur.value - prev.value) * k;
		}
	}

	return keyframes[keyframes.size() - 1].value;
}

template <typename T>
float LinearParameter<T>::getMaxTime()
{
	return keyframes[keyframes.size() - 1].time;
}

template class LinearParameter<float>;
template class LinearParameter<cocos2d::Vec2>;
template class LinearParameter<cocos2d::Vec3>;
template class LinearParameter<cocos2d::Vec4>;