#pragma once
#ifndef Light_h__
#define Light_h__

#include "luxMath.h"
#include "Ray.h"
namespace obj{
	
	class Light {
	public:
		Light(const lux::Vector &position,const lux::Color &light_color,const float &_intensity) :
			pos(position), lCol(light_color), intensity(_intensity){}
		virtual ~Light() {}
		const float getIntensity() const { return intensity; }
		const lux::Color getColor() const { return lCol; }
		virtual const Ray getlightRay(const lux::Vector p) { 
			lDir = (p - pos).unitvector();
			return Ray(pos, lDir);
		}
		virtual lux::Vector const getNormal(const lux::Vector p)
		{	
			return normal;
		}

	protected:
		lux::Vector lDir, pos, normal{};
		lux::Color lCol;
		float intensity;

	};

}


#endif // Light_h__