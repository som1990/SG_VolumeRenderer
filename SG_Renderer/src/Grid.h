#ifndef Grid_h__
#define Grid_h__

#include "luxMath.h"
#include <vector>
#include <iostream>

class DSMGrid
{
public:
	DSMGrid(lux::Vector _llc, lux::Vector _urc, float _gridSize) :
		llc(_llc), urc(_urc), gridLength(_gridSize) {
		lux::Vector size = urc - llc;
		xSize = ceil(abs(size.X()) / gridLength);
		ySize = ceil(abs(size.Y()) / gridLength);
		zSize = ceil(abs(size.Z()) / gridLength);
		//std::cout << "Grid Size: " << xSize << ", " << ySize << ", " << zSize << std::endl;
		data.resize(xSize*ySize*zSize,0.0);
		//std::cout << "Generated grid class!" << std::endl;
	}

	DSMGrid() {
		llc = lux::Vector(0, 0, 0);
		urc = lux::Vector(1, 1, 1);
		xSize = ySize = zSize = 100;
	}

	DSMGrid(const char* mapfile);

	~DSMGrid() {

	}

	void init(const lux::Vector &_llc, const lux::Vector &_urc,const float &_gridSize)
	{
		urc = _urc;
		llc = _llc;
		gridLength = _gridSize;
		lux::Vector size = urc - llc;
		xSize = ceil(abs(size.X()) / gridLength);
		ySize = ceil(abs(size.Y()) / gridLength);
		zSize = ceil(abs(size.Z()) / gridLength);
		data.resize(xSize*ySize*zSize, 0.0);
	}

	void insertData(const int &x,const int &y,const int &z, float _data);
	void clearData();
	void generateMap(const char* path);
	
	void readMap(const char* path);
	const float getGridLength() const { return gridLength; }
	const float getGridData(const int &i, const int &j, const int &k) const;
	const std::vector<float> &getGridMap() const { return data; }
	const lux::Vector getDimentions() const { return lux::Vector(xSize, ySize, zSize); }
	const lux::Vector getSign() const { 
		lux::Vector t = (urc - llc);
		return lux::Vector((t.X() > 0) - (t.X() < 0), (t.Y() > 0) - (t.Y() < 0), (t.Z() > 0) - (t.Z() < 0));
	}
	const std::vector<lux::Vector> getbounds() const {
		std::vector<lux::Vector> temp = { llc,urc };
		return temp; 
	}
	float trilinearInterp(const lux::Vector &p);

private:
	lux::Vector llc;
	lux::Vector urc;
	float gridLength;
	std::vector<float> data; 
	int xSize=0, ySize=0, zSize=0;
};

#endif // Grid_h__