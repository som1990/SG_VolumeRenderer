#pragma once
#ifndef Light_h__
#define Light_h__

#include "luxMath.h"
#include "Ray.h"
#include "LightData.h"
#include <omp.h>
#include <memory>

namespace obj{
	
	class Light {
	public:
		Light(const lux::Vector &position,const lux::Color &light_color,const float &_intensity) :
			pos(position), lCol(light_color), intensity(_intensity){}
		virtual ~Light() {}
		const float getIntensity() const { return intensity; }
		const lux::Color getColor() const { return lCol; }
		virtual const Ray getlightRay(const lux::Vector &p) { 
			lDir = (pos - p).unitvector();
			return Ray(pos, lDir);
		}
		virtual lux::Vector const getNormal(const lux::Vector p) const { return normal;}

		virtual const lux::Color eval(std::unique_ptr<LightData> &lData) {
			float lDist = (pos - lData->pos).magnitude();
			lDir = (pos - lData->pos).unitvector();
			lux::Vector x_L = lData->pos;

			int steps = floor(lData->lFarDist / lData->lStepSize);
			
			
			float DSM = 0;
			#pragma omp parallel for
			for (int i = 0; i < steps; i++) {
				float density = lData->density->eval(x_L);
				density = (density < 0) ? 0 : density;
				x_L += lData->lStepSize*lDir;
				if (density != 0)
				{
					DSM += density*lData->lStepSize;
				}

			}
			float T_L = exp(-lData->kappa * DSM);

			return (lCol * T_L);
		}

	protected:
		lux::Vector lDir, pos, normal{};
		lux::Color lCol;
		float intensity;


	};

}


#endif // Light_h__