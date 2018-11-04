#pragma once
#ifndef Light_h__
#define Light_h__

#include "luxMath.h"
#include "Ray.h"
#include "LightData.h"
#include "Grid.h"
#include <omp.h>
#include <memory>
#include <iostream>


namespace obj{
	
	class Light {
	public:
		Light(const lux::Vector &position,const lux::Color &light_color,const float &_intensity) :
			pos(position), lCol(light_color), intensity(_intensity){}
		virtual ~Light() {
		
		}
		const float getIntensity() const { return intensity; }
		const lux::Color getColor() const { return lCol; }
		virtual const Ray getlightRay(const lux::Vector &p) { 
			lDir = (pos - p).unitvector();
			return Ray(pos, lDir);
		}
		

		virtual  const lux::Vector getNormal(const lux::Vector p) const { return normal;}
		
		void setDSMGrid(const lux::Vector &llc, const lux::Vector &urc, const float &gridSize)
		{
			//std::cout << "Generating grid class!" << std::endl;
			grid = new DSMGrid(llc, urc, gridSize);
			
		}

		void genDSMGrid(std::unique_ptr<LightData> &lData, const char* path);
		virtual const lux::Color eval(std::unique_ptr<LightData> &lData); 
		void readDSMGrid(const char* path)
		{
			grid->readMap(path);
		}
		void clearDSMGrid() { delete grid; }

	protected:
		lux::Vector lDir, pos, normal{};
		lux::Color lCol;
		DSMGrid* grid;
		float intensity;	

	};

}


#endif // Light_h__