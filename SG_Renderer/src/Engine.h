#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "luxMath.h"
#include "Fields.h"
#include "CSG.h"
#include "transformations.h"
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include "VolumeObject.h"
#include "RenderSettings.h"
#include "AABBox.h"

namespace vol {
	void printMessage();
	
	class Engine 
	{
	public:
		Engine() {}
		void setRenderSettings(const RenderSettings& rend);
		void render(lux::Color* exr, int frame);
		void genDSM(const Scene &s1, int frameNum);
		void readDSM(const Scene& s1, int frameNum);
		AABBox* box = new AABBox(lux::Vector(0, 0, 0), lux::Vector(1, 1, 1));
	private:
		//Global Settings
		int xRes=500, yRes=500;
		float nearDist = 2, farDist = 10;
		int fStart = 1;
		int numFrames = 24;

		//Volume Render Setting
		float stepSize=0.01, kappa=50.0;

		//Light Settings
		float lStepSize = 0.1;
		float lGridSize = 0.2;
		bool gridedDSM = false;
		std::string mapData = "";
		bool animated_lights = false;

		lux::Color rayMarchEmission(const Scene &s1, const Ray &r);
		lux::Color rayMarchLights(const Scene &s1, const Ray &r);
		void generateImage(const Scene& s1, lux::Color* exr);
	};

}

#endif // __ENGINE_H__