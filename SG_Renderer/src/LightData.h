#pragma once
#ifndef LightData_h__
#define LightData_h__

#include "luxMath.h"
#include "Fields.h"


struct LightData {
	lux::Vector pos = lux::Vector(0,0,0);
	float kappa = 10;
	vol::VolumeFloatPtr volume;

	float lStepSize = 0.1;
	float lFarDist = 2.0;

	bool gridedDSM = 1;
	float lGridSize = 0.1;
};



#endif // LightData_h__