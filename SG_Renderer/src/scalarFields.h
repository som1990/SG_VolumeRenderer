
#ifndef scalarFields_h__
#define scalarFields_h__

#include "VolumeField.h"
#include <cmath>



namespace vol {

	class Sphere : public VolumeField<float>
	{
	public:
		Sphere(lux::Vector center, float radius) :
			cen(center), rad(radius) {}

		const float eval(const lux::Vector& p) const override
		{
			return rad - (p - cen).magnitude();
		}

	private:
		lux::Vector cen;
		float rad;
	};

	class Elipse : public VolumeField<float>
	{
	public:
		Elipse(lux::Vector center, lux::Vector normal, float radiusMajor, float radiusMinor) :
			cen(center), n(normal), rMajor(radiusMajor), rMinor(radiusMinor) {}

		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			float z = x*n;
			lux::Vector x_perp = x - z*n;
			float x_perpMag = x_perp.magnitude();
			float val = 1 - ((z*z) / (rMajor*rMajor)) - ((x_perpMag*x_perpMag) / (rMinor*rMinor));
			return val;
		}
	private:
		lux::Vector cen;
		lux::Vector n;
		float rMajor;
		float rMinor;
	};

	class Torus : public VolumeField<float>
	{
	public:
		Torus(lux::Vector center, lux::Vector normal, float radiusMajor, float radiusMinor) :
			cen(center), n(normal), rMajor(radiusMajor), rMinor(radiusMinor) {}
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			lux::Vector x_perp = x - (x*n)*n;
			float x_perpMag = x_perp.magnitude();
			float x_mag = x.magnitude();
			float y = x_mag*x_mag + rMajor*rMajor - rMinor*rMinor;
			float val = 4 * rMajor*rMajor*x_perpMag*x_perpMag - y*y;
			return val;
		}

	private:
		lux::Vector cen;
		lux::Vector n;
		float rMajor;
		float rMinor;
	};

	class Box : public VolumeField<float>
	{
	public:
		Box(lux::Vector center, float radius,  float pNorm) :
			cen(center), rad(radius), q(pNorm) {}
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			float val = powf(rad, 2.0 * q) - powf(x.X(), 2.0 * q) - powf(x.Y(), 2 * q) - powf(x.Z(), 2 * q);
			return val;
		}

	private:
		lux::Vector cen;
		float rad;
		float q;

	};

	class Plane : public VolumeField<float>
	{
	public:
		Plane(lux::Vector center, lux::Vector normal) :
			cen(center), n(normal) {} 
		
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = -(p - cen);
			return x*n;
		}
	
	private:
		lux::Vector cen;
		lux::Vector n;
	};

	class Cone : public VolumeField<float>
	{
	public:
		Cone(lux::Vector center, lux::Vector normal, float height, float maxAngle) :
			cen(center), n(normal), h(height), maxTheta(maxAngle) {}
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			float val = x*n;
			if (val < 0) 
			{
				return val;
			}
			else if (val > h)
			{
				return (h - val);
			}
			else if (val > 0 && val < h)
			{
				return (val - x.magnitude()*cos(maxTheta));
			}
		}

	private:
		lux::Vector cen;
		lux::Vector n;
		float h, maxTheta;
	};

	class Cylinder : public VolumeField<float>
	{
	public:
		Cylinder(lux::Vector center, lux::Vector normal, float radius) :
			cen(center), n(normal), rad(radius) {}
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			float y = (x - (x*n)*n).magnitude();
			return rad - y;
		}
	private:
		lux::Vector cen, n;
		float rad;
	};

	class Icosahedron : public VolumeField<float>
	{
	public:
		Icosahedron(lux::Vector center, float radius) :
			cen(center), rad(radius) {}
		const float eval(const lux::Vector& p) const override
		{
			const float PI = 3.14159265359;
			lux::Vector x = p - cen;
			float x_mag = x.magnitude();

			if (x_mag > 1.8*PI)
			{
				return (-1.8*PI);
			}
			else
			{
				float val = cos(x.X() + rad*x.Y()) + cos(x.X() - rad*x.Y()) +
							cos(x.Y() + rad*x.Z()) + cos(x.Y() - rad*x.Z()) +
							cos(x.Z() + rad*x.X()) + cos(x.Z() - rad*x.X()) - 2;
			}
		}

	private:
		lux::Vector cen;
		float rad;
	};

	class SteinerPatch : public VolumeField<float>
	{
	public:
		SteinerPatch(lux::Vector center) :
			cen(center) {}
		
		const float eval(const lux::Vector& p) const override
		{
			lux::Vector x = p - cen;
			float val = -(x.X()*x.X()*x.Y()*x.Y() + x.Y()*x.Y()*x.Z()*x.Z() - x.X()*x.Y()*x.Z());
			return val;
		}

	private:
		lux::Vector cen;
	};
}


#endif // scalarFields_h__