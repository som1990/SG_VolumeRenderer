#ifndef Ray_h__
#define Ray_h__

#include "luxMath.h"

class Ray
{
public:
	Ray(lux::Vector origin, lux::Vector direction) :
		o(origin), dir(direction) {
		dir.normalize();
	}

	const lux::Vector &getDir() const { return dir; }
	const lux::Vector &getOrigin() const { return o; }
	void setOrigin(const lux::Vector& origin) { o = origin; }
	void setDirection(const lux::Vector& direction) { 
		dir = direction; 
		dir.normalize();
	}

private:
	lux::Vector o;
	lux::Vector dir;
};

#endif // Ray_h__