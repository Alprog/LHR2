
#pragma once

#include <vector>
#include "Parameter.h"

template <typename T>
class Parameter;

template <typename T>
class SampledParameter : public Parameter<T>
{
	struct sample
	{
		T value;
		T delta;
	};

public:
	SampledParameter(Parameter<T>* refParameter, int sampleCount = 100);
	~SampledParameter();

	T getValue(float time) override;
	float getMaxTime() override { return maxTime; }

	inline T getValueBySample(int index)
	{
		return samples[index].value;
	}

	inline T getValueBySample(int index, float lerpPart)
	{
		auto& sample = samples[index];
		return sample.value + sample.delta * lerpPart;
	}

	int sampleCount;
	sample* samples;
	float maxTime;
};