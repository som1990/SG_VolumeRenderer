#ifndef RenderSettings_h__
#define RenderSettings_h__

#include <string.h>

struct RenderSettings {
	//Image Attributes
	int iWidth = 500;
	int iHeight = 500;

	//File I/O
	std::string mapDir = "";
	std::string renderDir = "";
	std::string fileName = "SG_Humanoid";
	//Frames
	int fBegin = 1;
	int fEnd = 2;
	int fInc = 1;

	//Camera Settings
	int nearDist = 2;
	int farDist = 10;

	//RayMarch Attributes
	float stepSize = 0.01;
	float kappa = 100.0;
	bool gridedVolume = false;
	float oGridSize = 0.1;

	//LIGHT SETTINGS
	//DSM Attributes
	float lStepSize = 0.1;
	float phase = 1.0f;
	bool gridedDSM = true;
	bool animated_Lights = false;
	
	//Grid Attributes
	float lGridSize = 0.01;
	

};

#endif // RenderSettings_h__
