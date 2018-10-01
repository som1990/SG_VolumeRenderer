#include "Camera.h"
#include <random>
#include <iostream>
#define PI 3.14159265359
namespace obj
{
	const Ray Camera::getRay(const int &i, const int &j, const int XPixels, const int YPixels)
	{
		float u, v;
		std::random_device rd1{};
		std::random_device rd2{};
		std::mt19937 gen(rd1());
		std::mt19937 gen2(rd2());
		std::uniform_real_distribution<double> dis(-0.5, 0.5);
		float rFOV = cHFov * PI/180;
		u = (-1 + (2 * (i + dis(gen))) / (XPixels - 1))* tan(rFOV/2);
		v = (-1 + (2 * (j + dis(gen2))) / (YPixels - 1))* tan(rFOV/2)/aspectRatio;

		lux::Vector uc, vc,nc;
		uc = ( cDir ^ cUp ).unitvector();
		vc = (uc ^ cDir).unitvector();
		nc = cDir.unitvector();

		lux::Vector qc = (uc * u) + (vc * v);
		lux::Vector n = (qc + nc).unitvector();
	//	std::cout << "up: " << cUp.X() << ", " << cUp.Y() << ", " << cUp.Z() << std::endl;
	//	std::cout << "vc: " << vc.X() << ", " << vc.Y() << ", " << vc.Z() << std::endl;
		return Ray(cE,n);

	} 
}
