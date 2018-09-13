#include "Engine.h"
#include <iostream>

namespace vol {
	void printMessage() {
		std::cout << "Hello World" << std::endl;
		std::cin.get();
	} 
	void render() {
		Sphere *S = new Sphere(lux::Vector(0, 0, 0), 2);
		Elipse *E = new Elipse(lux::Vector(0, 0, 0), lux::Vector(0, 1, 0), 2, 1);
		Torus *T = new Torus(lux::Vector(0, 0, 0), lux::Vector(0, 1, 0), 2, 1);
		Box *B = new Box(lux::Vector(0, 0, 0), 2, 1.2);
		Plane *P = new Plane(lux::Vector(0, 0, 0), lux::Vector(0, 1, 0));
		
		float val = S->eval(lux::Vector(0, 0, 0));
		float val2 = E->eval(lux::Vector(0, 0, 0));
		float val3 = T->eval(lux::Vector(-1, 0, 1));
		float val4 = B->eval(lux::Vector(0, 0, 0));
		float val5 = P->eval(lux::Vector(-1, 0, 1));

		Translate<VolumeFloatPtr,float> trans(S, lux::Vector(0, 0, 1));
		float sphere2 = trans.eval(lux::Vector(0, 0, 0));


		ScalarFieldAdd t1 = *S + *E;
		VolumeField<float> t2 = ScalarFieldAdd(S,E);
		//float temp1 = t.eval(lux::Vector(-1, 0, 1));
		float temp1 = t1.eval(lux::Vector(0, 0, 0));
		//float temp2 = t2.eval(lux::Vector(0, 0, 0));

		//VolumeField<float>* t = (VolumeField<float>*)S + (VolumeField<float>*)E;
		std::cout << "S + E: " << temp1 << std::endl;
		std::cout << "Translate(S,[0,0,1]): " << sphere2 << std::endl;
		//std::cout << "S + E(Method2): " << temp1 << std::endl;
		std::cout << "S: " << val << std::endl;
		std::cout << "E: " << val2 << std::endl;
		std::cout << "B: " << val4 << std::endl;
		std::cin.get();
		delete S, E, T, B, P;
	}
}