
#pragma once

#include "EmitterSettings.h"

struct SystemSettings
{
	SystemSettings();
		
	float emissionFrequency; // Hz
	
	EmitterSettings emitter;
};