#ifndef AABBox_h__
#define AABBox_h__

#include "luxMath.h"
#include "Ray.h"
#include <assert.h>

class AABBox {
public:
	AABBox(const lux::Vector &llc, const lux::Vector &urc) {
		assert(llc < urc);
		bounds[0] = llc;
		bounds[1] = urc;
	}
	AABBox() {
		bounds[0] = lux::Vector(0, 0, 0);
		bounds[1] = lux::Vector(1, 1, 1);
	}
	bool intersect(const Ray &, float nearDist, float farDist) const;
	void setBounds(const lux::Vector &llc, const lux::Vector &urc);
	const lux::Vector *getBounds() const { return bounds; }
private:
	lux::Vector bounds[2];
};

#endif // AABBox_h__

