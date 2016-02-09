
#pragma once

#include "math/Vec3.h"
#include "base/CCTypes.h"

struct Particle 
{
	// birth const:
		float lifeTime;
		cocos2d::Vec3 direction;	

	// frame const:
		float updateTime;

	// over life parameters:
		float size;
		float speed;
		cocos2d::Vec4 color;

	// generic:
		float curTime;
		cocos2d::Vec3 position;
		cocos2d::Vec3 accSpeedVector;

	// sample info for performance calculation: 
	int sampleIndex;
	float sampleLerpPart;

	inline bool isAlive() { return curTime < lifeTime; }
};