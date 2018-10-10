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
		void render(lux::Color* exr);
		AABBox* box = new AABBox(lux::Vector(0, 0, 0), lux::Vector(1, 1, 1));
	private:
		int xRes=500, yRes=500;
		float stepSize=0.01, kappa=50.0;
		float nearDist=2, farDist=10;

		lux::Color rayMarch(const Scene &s1, const Ray &r);
		void generateImage(const Scene& s1, lux::Color* exr);
	};


}

#endif // __ENGINE_H__