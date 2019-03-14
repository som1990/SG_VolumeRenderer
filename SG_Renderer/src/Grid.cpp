#include "Grid.h"
#include "ParallelStream.h"
#include <fstream>

DSMGrid::DSMGrid(const char* path)
{
	std::ifstream ifile(path, std::ios_base::binary);
	lux::Vector _urc, _llc;

	ifile.read(reinterpret_cast<char *>(&_llc), sizeof(lux::Vector));
	ifile.read(reinterpret_cast<char *>(&_urc), sizeof(lux::Vector));
	urc = _urc;
	llc = _llc;
	//std::cout << "I've reached ReadMap" << std::endl;
	size_t nx, ny, nz;
	ifile.read(reinterpret_cast<char*>(&nx), sizeof(size_t));
	ifile.read(reinterpret_cast<char*>(&ny), sizeof(size_t));
	ifile.read(reinterpret_cast<char*>(&nz), sizeof(size_t));

	size_t vSize = nx * ny * nz;
	std::cout << (ParallelStream() << "Reading nx, ny, nz:  " << nx << ", " << ny << ", " << nz).toString() << std::endl;
	data.resize(vSize * sizeof(float));
	xSize = nx;
	ySize = ny;
	zSize = nz;
	float gLen;
	ifile.read(reinterpret_cast<char *>(&gLen), sizeof(float));
	gridLength = gLen;
	if (vSize != 0)
	{
		ifile.read(reinterpret_cast<char*>(&data[0]), vSize * sizeof(float));
	}
	ifile.close();
}

void DSMGrid::insertData(const int &x, const int &y, const int &z, float _data)
{
	int index = x + xSize * (y + ySize * z);
	data[index] = _data;
}

void DSMGrid::generateMap(const char* path)
{
	std::ofstream  ofile(path, std::ios_base::binary);

	size_t nx = xSize;
	size_t ny = ySize;
	size_t nz = zSize;
	float gLen = gridLength;
	size_t size = nx * ny * nz;
	lux::Vector _llc, _urc;
	_llc = llc;
	_urc = urc;
	std::cout << (ParallelStream() << "Writing nx, ny, nz:  " << nx << ", " << ny << ", " << nz ).toString() << std::endl;
	ofile.write(reinterpret_cast<char *>(&_llc), sizeof(lux::Vector));
	ofile.write(reinterpret_cast<char *>(&_urc), sizeof(lux::Vector));
	ofile.write(reinterpret_cast<char *>(&nx), sizeof(size_t));
	ofile.write(reinterpret_cast<char *>(&ny), sizeof(size_t));
	ofile.write(reinterpret_cast<char *>(&nz), sizeof(size_t));
	ofile.write(reinterpret_cast<char *>(&gLen), sizeof(float));
	ofile.write(reinterpret_cast<char *>(&data[0]), size * sizeof(float));
	/*for (int i = 0; i < xSize; i++)
	{
		for (int j = 0; j < ySize; j++)
		{
			for (int k = 0; k < zSize; k++)
			{
				int index = i + xSize * (j + ySize * k);
				ofile.write((char*)&data[index], sizeof(float));
			}
		}
	}*/
	ofile.close();
}

void DSMGrid::clearData()
{
	data.resize(xSize*ySize*zSize,0.0);
}

void DSMGrid::readMap(const char* path)
{
	std::ifstream ifile(path, std::ios_base::binary);
	lux::Vector _urc, _llc;
	
	ifile.read(reinterpret_cast<char *>(&_llc), sizeof(lux::Vector));
	ifile.read(reinterpret_cast<char *>(&_urc), sizeof(lux::Vector));
	urc = _urc;
	llc = _llc;
	//std::cout << "I've reached ReadMap" << std::endl;
	size_t nx,ny,nz;
	ifile.read(reinterpret_cast<char*>(&nx), sizeof(size_t));
	ifile.read(reinterpret_cast<char*>(&ny), sizeof(size_t));
	ifile.read(reinterpret_cast<char*>(&nz), sizeof(size_t));

	size_t vSize = nx * ny * nz;
	std::cout << (ParallelStream() << "Reading nx, ny, nz:  " << nx << ", " << ny << ", " << nz).toString() << std::endl;
	data.resize(vSize*sizeof(float));
	xSize = nx;
	ySize = ny;
	zSize = nz;
	float gLen;
	ifile.read(reinterpret_cast<char *>(&gLen), sizeof(float));
	gridLength = gLen;
	if (vSize != 0)
	{
		ifile.read(reinterpret_cast<char*>(&data[0]), vSize * sizeof(float));
	}
	ifile.close();
	std::cout << "Read DSM GridLen: " << gridLength << std::endl;
}

const float DSMGrid::getGridData(const int &i, const int &j, const int &k) const
{
	int index = i + xSize * (j + ySize * k);

	//std::cout << (ParallelStream() << "\n Index: " << index << " i, j, k : " << i << ", " << j << ", " << k ).toString() << std::endl;
	//std::cout << (ParallelStream() << "\n dataSize: " << data.size()).toString() << std::endl;
	return data[index];
}

float DSMGrid::trilinearInterp(const lux::Vector &p)
{
	
	lux::Vector gPos = p - llc;
	int x0 = int(gPos.X() / gridLength);
	int y0 = int(gPos.Y() / gridLength);
	int z0 = int(gPos.Z() / gridLength);

	if (x0 < 0 || y0 < 0 || z0 < 0)
		return 0;
//	std::cout << (ParallelStream() << "\n p: " << p.X() << ", " << p.Y() << ", " << p.Z()).toString() << std::endl;

//	std::cout << (ParallelStream() << "\n x0,y0,z0: " << x0 << " , " << y0 << " , " << z0).toString() << std::endl;
	int x1 = x0 + 1; int y1 = y0 + 1; int z1 = z0 + 1;
	x1 = (x1 < (xSize - 1)) ? x1 : (xSize - 1);
	y1 = (y1 < (ySize - 1)) ? y1 : (ySize - 1);
	z1 = (z1 < (zSize - 1)) ? z1 : (zSize - 1);

	float x_d = (gPos.X()/gridLength) - x0;
	float y_d = (gPos.Y()/gridLength) - y0;
	float z_d = (gPos.Z()/gridLength) - z0;

//	std::cout << (ParallelStream() << "\n x_d,y_d,z_d: " << x_d << ", " << y_d << ", " << z_d).toString() << std::endl;

	float c000 = getGridData(x0, y0, z0);
	float c100 = getGridData(x1, y0, z0);
	float c001 = getGridData(x0, y0, z1);
	float c101 = getGridData(x1, y0, z1);
	float c010 = getGridData(x0, y1, z0);
	float c110 = getGridData(x1, y1, z0);
	float c011 = getGridData(x0, y1, z1);
	float c111 = getGridData(x1, y1, z1);

	//std::cout << c000 << std::endl;

	float c00 = c000 * (1 - x_d) + c100 * x_d;
	float c01 = c001 * (1 - x_d) + c101 * x_d;
	float c10 = c010 * (1 - x_d) + c110 * x_d;
	float c11 = c011 * (1 - x_d) + c111 * x_d;

	float c0 = c00 * (1 - y_d) + c10 * y_d;
	float c1 = c01 * (1 - y_d) + c11 * y_d;

	float c = c0 * (1 - z_d) + c1 * z_d;

	return c;
}
