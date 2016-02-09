
#include "SampledParameter.h"
#include <algorithm>
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"

template <typename T>
SampledParameter<T>::SampledParameter(Parameter<T>* refParameter, int sampleCount)
{
	this->sampleCount = sampleCount;

	auto maxTime = refParameter->getMaxTime();

	samples = new sample[sampleCount + 1];

	samples[sampleCount] = { refParameter->getValue(maxTime), T() };

	for (int i = sampleCount - 1; i >= 0; i--)
	{
		float t = maxTime * i / sampleCount;

		T value = refParameter->getValue(t);
		T delta = samples[i + 1].value - value;
		samples[i] = { value, delta };
	}

}

template <typename T>
SampledParameter<T>::~SampledParameter()
{
	delete[] samples;
	samples = nullptr;
}

template <typename T>
T SampledParameter<T>::getValue(float time)
{
	float k = std::min(std::max(0.0f, time / maxTime), 1.0f) * sampleCount;

	int sampleIndex = int(k);
	float lerpPart = k - sampleIndex;

	return getValueBySample(sampleIndex, lerpPart);
}

template class SampledParameter<float>;
template class SampledParameter<cocos2d::Vec2>;
template class SampledParameter<cocos2d::Vec3>;
template class SampledParameter<cocos2d::Vec4>;