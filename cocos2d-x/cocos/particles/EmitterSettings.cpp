
#include "EmitterSettings.h"

inline float lerp(float a, float b, float k)
{
	return a + k * (b - a);
}

cocos2d::Vec3 randomDirection()
{
	return cocos2d::Vec3(cocos2d::rand_minus1_1(), cocos2d::rand_minus1_1(), cocos2d::rand_minus1_1()).getNormalized();
}


EmitterSettings::EmitterSettings()
{

}

EmitterSettings EmitterSettings::lerp(EmitterSettings& a, EmitterSettings& b, float k)
{
	if (k <= 0) { return a;	}
	if (k >= 1) { return b; }

	EmitterSettings s;
	s.position = a.position.lerp(b.position, k);
	s.particleLifetime = ::lerp(a.particleLifetime, b.particleLifetime, k);
	return s;
}

Particle EmitterSettings::emit()
{
	Particle particle;
	particle.curTime = 0;
	particle.lifeTime = this->particleLifetime;

	particle.position = cocos2d::Vec3(0, 0, 0);
	particle.direction = randomDirection();
		
	return particle;
}