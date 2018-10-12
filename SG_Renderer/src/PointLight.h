#pragma once
#ifndef PointLight_h__
#define PointLight_h__

#include "Light.h"

namespace obj {
	class PointLight : public Light {
	public:
		PointLight(const lux::Vector &position, const lux::Color &light_color, const float &_intensity) :
			Light(position,light_color,_intensity) {}
		
		const Ray getlightRay(const lux::Vector p)
		{
			lDir = (p - pos).unitvector();
			return Ray(pos, lDir);
		}

		const lux::Vector getNormal(const lux::Vector p)
		{
			normal = p - pos.unitvector();
			return normal;
		}

	private:

	};

}

#endif // PointLight_h__
