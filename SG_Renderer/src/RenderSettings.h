#ifndef RenderSettings_h__
#define RenderSettings_h__
struct RenderSettings {
	//Image Attributes
	int iWidth = 500;
	int iHeight = 500;

	//Frames
	int fBegin = 1;
	int fEnd = 24;
	int fInc = 1;

	//Camera Settings
	int nearDist = 2;
	int farDist = 10;

	//RayMarch Attributes
	float stepSize = 0.01;
	float kappa = 1000.0;

	//DSM Attributes
	float lStepSize = 0.1;
	float phase = 1.0f;

};

#endif // RenderSettings_h__
