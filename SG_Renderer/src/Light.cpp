#include "Light.h"
#include <iomanip>
#include "ParallelStream.h"

void obj::Light::genDSMGrid(std::unique_ptr<LightData> &lData, const char* path)
{

	lux::Vector dims = grid->getDimentions();
	lux::Vector gridSign = grid->getSign();
	std::vector<lux::Vector> bounds = grid->getbounds();
	std::cout << "Grid Dimensions: " << dims.X() << ", " << dims.Y() << ", " << dims.Z() << std::endl;
	std::cout << "Grid Length: " << grid->getGridLength() << std::endl;
	lux::Vector x_L;
	float val = 0;
	float invSize = 1 / (dims.X()*dims.Y()*dims.Z());
	for (int k = 0; k < int(dims.Z()); k++)
	{
		for (int j = 0; j < int(dims.Y()); j++)
		{
			#pragma omp parallel for
			for (int i = 0; i < int(dims.X()); i++)
			{
				x_L = bounds[0] + lux::Vector(i*gridSign.X(), j*gridSign.Y(), k*gridSign.Z())*grid->getGridLength();
				
				float lDist = (pos - x_L).magnitude();
				lux::Vector dir = (pos - x_L).unitvector();

				int steps = floor(lData->lFarDist / lData->lStepSize);
				float density = 0;
				float DSM = 0;
				#pragma omp parallel for 
				for (int s = 0; s < steps; s++)
				{
					density = lData->volume->eval(x_L);
					density = (density < 0) ? 0 : density;
					x_L += lData->lStepSize*dir;

					if (density != 0)
					{
						DSM += density * lData->lStepSize;
					}

				}
				//std::cout << "Pregrided DSM: " << DSM << std::endl;
				grid->insertData(i, j, k, DSM);
				float index = i + dims.X()*(j + dims.Y()*k);
				val = (round(index*invSize * 10000) / 100);
				
			}
			std::cout << "Calculating Map.... " << std::setprecision(2) << std::fixed << val << "%" << '\r' << std::flush;
		}
		
	}


	std::cout << "Map Calculated" << std::endl;
	std::cout << "Writing Map to " << path << std::endl;
	grid->generateMap(path);
}

const lux::Color obj::Light::eval(std::unique_ptr<LightData> &lData)
{
	
	float lDist = (pos - lData->pos).magnitude();
	lDir = (pos - lData->pos).unitvector();
	lux::Vector x_L = lData->pos;

	int steps = floor(lData->lFarDist / lData->lStepSize);
	//std::cout << (ParallelStream() << "stepsize: " << lData->lStepSize).toString() << std::endl;
	float density = 0;
	float DSM = 0;
	float gDSM = 0;
	if (lData->gridedDSM)
	{
		DSM = grid->trilinearInterp(x_L);
		//std::cout << "Grid DSM: " << DSM << std::endl;
	}
	else
	{
	//	std::cout << "Not using Map: " << std::endl;
		#pragma omp parallel for
		for (int i = 0; i < steps; i++) {
			density = lData->volume->eval(x_L);
			//std::cout << "density: " << density << std::endl;
			density = (density < 0) ? 0 : density;
			x_L += lData->lStepSize*lDir;
			if (density != 0)
			{
				DSM += density * lData->lStepSize;
			}

		}
	}	
	//	std::cout << "Ungridded DSM: " << DSM << std::endl;
	float T_L = exp(-lData->kappa * DSM);

	return (lCol * T_L);
}



