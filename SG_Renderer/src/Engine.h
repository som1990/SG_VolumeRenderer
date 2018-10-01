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

namespace vol {
	void printMessage();
	void render(lux::Color* exr, int iWidth, int iHeight);


}

#endif // __ENGINE_H__