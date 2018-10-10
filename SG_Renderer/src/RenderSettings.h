#pragma once
#ifndef RenderSettings_h__
#define RenderSettings_h__
struct RenderSettings {
	//Image Attributes
	int iWidth = 500;
	int iHeight = 500;


	//Camera Settings
	int nearDist = 2;
	int farDist = 10;

	//RayMarch Attributes
	float stepSize = 0.01;
	float kappa = 1000.0;


};

#endif // RenderSettings_h__
