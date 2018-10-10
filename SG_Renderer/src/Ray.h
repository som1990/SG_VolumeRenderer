#ifndef Ray_h__
#define Ray_h__

#include "luxMath.h"

class Ray
{
public:
	Ray(lux::Vector origin, lux::Vector direction) :
		o(origin), dir(direction) {
		dir.normalize();
		inv_dir = lux::Vector(1 / dir.X(), 1 / dir.Y(), 1 / dir.Z());
		sign[0] = (inv_dir.X() < 0);
		sign[1] = (inv_dir.Y() < 0);
		sign[2] = (inv_dir.Z() < 0);
	}

	const lux::Vector &getDir() const { return dir; }
	const lux::Vector &getOrigin() const { return o; }
	const lux::Vector &getInvDir() const { return inv_dir; }
	void setOrigin(const lux::Vector& origin) { o = origin; }
	void setDirection(const lux::Vector& direction) { 
		dir = direction; 
		dir.normalize();
		inv_dir = lux::Vector(1 / dir.X(), 1 / dir.Y(), 1 / dir.Z());
		sign[0] = (inv_dir.X() < 0);
		sign[1] = (inv_dir.Y() < 0);
		sign[2] = (inv_dir.Z() < 0);

	}
	int sign[3];
private:
	lux::Vector o;
	lux::Vector dir;
	lux::Vector inv_dir;
	
};

#endif // Ray_h__