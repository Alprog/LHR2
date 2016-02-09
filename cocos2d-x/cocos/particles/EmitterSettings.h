
#pragma once

#include "math/Vec3.h"
#include "Particle.h"

struct EmitterSettings
{
	EmitterSettings();

	static EmitterSettings lerp(EmitterSettings& a, EmitterSettings& b, float k);
	
	Particle emit();

	cocos2d::Vec3 position;
	float particleLifetime;
};