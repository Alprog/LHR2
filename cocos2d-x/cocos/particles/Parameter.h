
#pragma once

#include "SampledParameter.h"

template <typename T>
class SampledParameter;

class IParameter
{
public:
	virtual float getMaxTime() = 0;
	virtual IParameter* Sampling(int count) = 0;
};

template <typename T>
class Parameter : public IParameter
{
public:
	virtual T getValue(float time) = 0;
	
	virtual IParameter* Sampling(int count) override
	{
		return new SampledParameter<T>(this, count);
	}
};