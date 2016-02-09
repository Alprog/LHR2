
#pragma once

enum class ParameterType
{
	EmissionFrequency,
	ParticleLifetime,

	OverLifeSize,
	OverLifeSpeed,
	OverLifeColor,

	COUNT
};


const int ParameterCount = (int)ParameterType::COUNT;