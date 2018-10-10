#include "AABBox.h"

bool AABBox::intersect(const Ray &r, float t0, float t1) const
{

	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	tmin = (bounds[r.sign[0]].X() - r.getOrigin().X())* r.getInvDir().X();
	tmax = (bounds[1 - r.sign[0]].X() - r.getOrigin().X()) * r.getInvDir().X();
	tymin = (bounds[r.sign[1]].Y() - r.getOrigin().Y())* r.getInvDir().Y();
	tymax = (bounds[1 - r.sign[1]].Y() - r.getOrigin().Y()) * r.getInvDir().Y();

	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;



	tzmin = (bounds[r.sign[2]].Z() - r.getOrigin().Z()) * r.getInvDir().Z();
	tzmax = (bounds[1 - r.sign[2]].Z() - r.getOrigin().Z()) * r.getInvDir().Z();
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return ((tmin < t1) && (tmax > t0));
}



void AABBox::setBounds(const lux::Vector &llc, const lux::Vector &urc)
{
	assert(llc < urc);
	bounds[0] = llc;
	bounds[1] = urc;
}

