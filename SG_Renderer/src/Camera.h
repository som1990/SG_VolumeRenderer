#ifndef Camera_h__
#define Camera_h__
#include "luxMath.h"


namespace obj
{
	class Camera
	{
	public:
		Camera(lux::Vector position, lux::Vector direction, lux::Vector upDir, float fov, float aRatio) :
			cE(position), cDir(direction), cUp(upDir), cHFov(fov), aspectRatio(aRatio) {}

		const lux::Vector evalDir(const int &i, const int &j, const int XPixels, const int YPixels);
		const lux::Vector getposition() const { return cE; }
		const lux::Vector getviewDir() const { return cDir; }
		void setposition(const lux::Vector &pos) { cE = pos;}
		void setviewDir(const lux::Vector &dir) { cDir = dir;}
		

	private:
		lux::Vector cE;
		lux::Vector cDir;
		lux::Vector cUp;
		float cHFov;
		lux::Vector cVr;
		float aspectRatio;
	};
}
#endif // Camera_h__
