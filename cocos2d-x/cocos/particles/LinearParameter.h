
#pragma once

#include "Parameter.h"
#include <vector>

template <typename T>
class LinearParameter : public Parameter<T>
{
protected:
	struct keyframe
	{
		float time;
		T value;
	};

public:
	LinearParameter(std::vector<float>& times, std::vector<T>& values);

	virtual T getValue(float time) override;
	virtual float getMaxTime() override;

protected:
	std::vector<keyframe> keyframes;
};