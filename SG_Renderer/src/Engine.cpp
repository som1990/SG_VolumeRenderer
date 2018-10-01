#include "Engine.h"
#include <iostream>
#include <algorithm>
#include <cmath>

#define PI 3.14159265359

struct RenderSettings{
//Image Attributes
	int iWidth = 500;
	int iHeight = 500;


//Camera Settings
	int nearDist = 2;
	int farDist = 10;

//RayMarch Attributes
	float stepSize = 0.01;
	float kappa = 50.0;


};

static float clamp(float a, float low, float high)
{
	a = (a < low) ? low : ((a > high) ? high : a);
	return a;
}

namespace vol {
	void printMessage() {
		std::cout << "Hello World" << std::endl;
		std::cin.get();
	} 
	void testScene(Scene &s1){
		lux::Color *c_body = new lux::Color(0.600, 0.816, 0.894, 1.0);
		lux::Color *c_eyes = new lux::Color(0.373, 0.075, 0.216, 1.0);
		lux::Color *c_feet = new lux::Color(0.996, 0.855, 0.235,1.0);
		lux::Color *c_dim = new lux::Color(0.980, 0.733, 0.733, 1.0);
		lux::Color *c_Turban = new lux::Color(0.913,0.40,0.0,1.0);
		lux::Color *c_Turban2 = new lux::Color(0.286, 0, 0.329,1.0);
		lux::Color *c_GREEN = new lux::Color(0, 1.0, 0, 1.0);
		lux::Color *c_stomach = new lux::Color(0.886, 0.961, 0.988,1.0);

		Sphere *S = new Sphere(lux::Vector(0, 0, 0), 2);
		
		Torus *T = new Torus(lux::Vector(0, 0, 0), lux::Vector(0, 1, 0), 2, 1);
		
		Plane *P = new Plane(lux::Vector(0, 0, 0), lux::Vector(0, 1, 0));


		//Body
		Box *B1 = new Box(lux::Vector(0, 1.654, 0), 1.829*0.5, 8);
		SolidColorField *C1 = new SolidColorField(c_body);

		//Arms
		Elipse *A1 = new Elipse(lux::Vector(0.976, 1.499, 0.020), lux::Vector(0.584, -0.812, 0), 0.587, 0.175);
		Elipse *A2 = new Elipse(lux::Vector(-0.861, 1.629, 0.02), lux::Vector(0.661,0.75, 0), 0.587, 0.175);
		ScalarFieldUnion* Arms = new ScalarFieldUnion(A1, A2);
		ScalarFieldUnion* body = new ScalarFieldUnion(B1, Arms);

		//Dimples 
		Sphere *SDimR = new Sphere(lux::Vector(0.721, 1.203, 0.816), 0.127);
		Sphere *SDimL = new Sphere(lux::Vector(-0.666, 1.203, 0.816), 0.127);
		SolidColorField *C_Pink = new SolidColorField(c_dim);
		ScalarFieldUnion* Dim = new ScalarFieldUnion(SDimL, SDimR);

		//Eyes
		Elipse *E1 = new Elipse(lux::Vector(0.484, 1.571, 0.936), lux::Vector(0, 1, 0), 0.293, 0.201);
		SolidColorField *C2 = new SolidColorField(c_eyes);
		Elipse *E2 = new Elipse(lux::Vector(-0.419, 1.551, 0.919), lux::Vector(0, 1, 0), 0.293, 0.201);
		ScalarFieldUnion* Eyes = new ScalarFieldUnion(E1, E2);

		ClampColorFields* Ctest = new ClampColorFields(C2, E1, C2, E2);
		ClampColorFields* C3 = new ClampColorFields(C1, body, Ctest, Eyes);
		//ClampColorFields* Ctest2 = new ClampColorFields(Ctest, Eyes, C1, B1);


		//Feet
		Sphere *SR = new Sphere(lux::Vector(0.821, 0.869, 1.078), 0.253);
		Sphere *SL = new Sphere(lux::Vector(-0.776, 0.869, 1.078), 0.253);
		ScalarFieldUnion* Feet = new ScalarFieldUnion(SR, SL);
		
		
		//Nose
		Cone *Nose = new Cone(lux::Vector(0.052, 1.306, 1.65), lux::Vector(0, 0, -1), 1, 20.0);
		ScalarFieldUnion* Feet_Nose = new ScalarFieldUnion(Feet, Nose);
		SolidColorField* CFeet = new SolidColorField(c_feet);
		//lux::Vector rotAngle(0, -1.0*0.5*PI, 0);
		//ScalarFieldRotate* NoseRot = new ScalarFieldRotate(Nose, rotAngle);

		//Stomach
		lux::Vector nStomach = lux::Vector(0, 0, 1);
		lux::Vector posStomach = lux::Vector(0.04, 0.588, 0.294);
		float hStomach = 0.656;
		Cylinder *Stomach = new Cylinder(posStomach, nStomach, 0.495);
		SolidColorField *CStomach = new SolidColorField(c_stomach);
		lux::Vector planeTop = (posStomach + nStomach * hStomach) / 2.0f;
		lux::Vector planeBot = (posStomach - nStomach * hStomach) / 2.0f;
		Plane *cTop = new Plane(planeTop, nStomach);
		Plane *cBottom = new Plane(planeBot, nStomach);
		Plane *cHalf = new Plane(posStomach, lux::Vector(0, -1, 0));
		ScalarFieldIntersection *Tummy1 = new ScalarFieldIntersection(cTop, Stomach);
		ScalarFieldIntersection *Tummy2 = new ScalarFieldIntersection(cBottom, Tummy1);
		ScalarFieldIntersection *Tummy = new ScalarFieldIntersection(cHalf, Tummy2);

		//Turban
		Torus *Turban_1 = new Torus(lux::Vector(0.0, 2.583, 0.0), lux::Vector(0.0, 0.980, -0.198), 1.0, 0.5);
		SolidColorField* CTurban_1 = new SolidColorField(c_Turban);
		Torus *Turban_2 = new Torus(lux::Vector(0.0, 3.014, 0.0), lux::Vector(0.0, 0.980, -0.198), 0.665, 0.5*0.665);
		ScalarFieldUnion *Turban_3 = new ScalarFieldUnion(Turban_1, Turban_2);
		ClampColorFields *CTurban3 = new ClampColorFields(CTurban_1, Turban_1, C2, Turban_2);

		Icosahedron *Turban_4 = new Icosahedron(lux::Vector(0, 0, 0), 1.61803399);
		ScalarFieldScale *sTurban_4 = new ScalarFieldScale(Turban_4, 0.15*0.946);
		ScalarFieldTranslate *tsTurban_4 = new ScalarFieldTranslate(sTurban_4, lux::Vector (0, 2.955, -0.069));
		SolidColorField* CTurban4 = new SolidColorField(c_Turban2);
		
		SteinerPatch *Turban_5 = new SteinerPatch(lux::Vector(0, 3.43, 1.341));
		SolidColorField *CTurban5 = new SolidColorField(c_GREEN);
		//ScalarFieldTranslate *tTurban_5 = new ScalarFieldTranslate(Turban_5, lux::Vector(0, 2.794, 2.015));
		ScalarFieldUnion *Turban_6 = new ScalarFieldUnion(Turban_3, Turban_5);
		ClampColorFields *CTurban6 = new ClampColorFields(C1, Turban_5, CTurban3, Turban_3);

		ScalarFieldUnion *Turban = new ScalarFieldUnion(Turban_6, tsTurban_4);
		ClampColorFields *CTurban = new ClampColorFields(CTurban6, Turban_6, CTurban4, tsTurban_4);

		//Figure
		ScalarFieldUnion* fig1 = new ScalarFieldUnion(Eyes, body);
		ScalarFieldUnion* fig2 = new ScalarFieldUnion(fig1, Feet_Nose);
		
		ClampColorFields *CFig2 = new ClampColorFields(CFeet, Feet_Nose, C3, fig1);
		ScalarFieldUnion* fig3 = new ScalarFieldUnion(fig2, Dim);
		ClampColorFields *CFig3 = new ClampColorFields(CFig2, fig2, C_Pink, Dim);

		ScalarFieldUnion* fig4 = new ScalarFieldUnion(fig3, Turban);
		ClampColorFields *Cfig4 = new ClampColorFields(CFig3, fig3, CTurban, Turban);
		
		ScalarFieldUnion *model = new ScalarFieldUnion(fig4, Tummy);
		ClampColorFields *Cmodel = new ClampColorFields(Cfig4, fig4, CStomach, Tummy);


		lux::Vector rotAngle(0, -1.0*0.5*PI, 0);
		
		ScalarFieldRotate* sRot = new ScalarFieldRotate(fig4, rotAngle);
		ColorFieldRotate* cRot = new ColorFieldRotate(Cfig4, rotAngle);
		
		//VolumeFloatPtr fig2 = new ScalarFieldScale(fig, 2);

		std::shared_ptr<obj::VolumeObject> o1 = std::make_shared<obj::VolumeObject>(Tummy, CStomach, nullptr, nullptr);
		s1.addObject("Body", o1);
	}

	lux::Color rayMarch(const Scene &s1, const Ray &r, const RenderSettings& parms)
	{
		int steps = (parms.farDist - parms.nearDist)/parms.stepSize;
		float k = parms.kappa;
		lux::Vector x = r.getOrigin() + r.getDir()*parms.nearDist;
		//std::cout << "Position: " << x.X() << ", " << x.Y() << ", " << x.Z() << std::endl;
		std::string var = "Body";
		std::shared_ptr<obj::VolumeObject> s = s1.getObject(var);

		VolumeFloatPtr density = s->getScalarField();
		
	//	std::cout << density->eval(lux::Vector(0, 0, 0)) << std::endl;
		//ClampColorFields* color = (ClampColorFields*)s->getColorField();
		VolumeColorPtr color = s->getColorField();
		//lux::Color c1 = color->eval(lux::Vector(0, 0, 0));
	//	std::cout << "Color: " << c1[0] << ", " << c1[1] << ", " << c1[2]<< std::endl;
		float T = 1;
		lux::Color L(0,0,0,1.0);
//		std::cout << "InitColor: " << L[0] << ", " << L[1] << ", " << L[2] << std::endl;
		#pragma omp parallel for
		for (int i = 0; i < steps; i++)
		{
			x += r.getDir()*parms.stepSize;
			float val = clamp(density->eval(x), 0, 1);
			if (val != 0)
			{
				float dT = std::exp(-parms.kappa*parms.stepSize*val);
				L += color->eval(x) * (1 - dT)*T;
				//std::cout << "BuildColor: " << L[0] << ", " << L[1] << ", " << L[2] << std::endl;
				T *= dT;
			}
		}
		L[3] = 1-T;
		//std::cout << "Color: " << L[0] << ", " << L[1] << ", " << L[2] << ", " << L[3] <<std::endl;
		//delete color;
		return L;
	}


	void generateImage(const Scene& s1, const RenderSettings& parms, lux::Color* exr)
	{
		std::shared_ptr<obj::Camera> cam = s1.getCam();
		//std::cout << "Rendering Image: "
		//lux::Vector v = cam->evalDir(0, 0, 1024, 720);
		//std::cout << "v: " << v.X() << ", " << v.Y() << ", " << v.Z() << std::endl;
		for (int j = 0; j < parms.iHeight; j++)
		{
		#pragma omp parallel for
			for (int i = 0; i < parms.iWidth; i++)
			{
				int index = i + parms.iWidth*j;
				Ray v = cam->getRay(i,j,parms.iWidth,parms.iHeight);
				lux::Color c = rayMarch(s1, v, parms);
				exr[index] = c;
			}
		}
	}

	void render(lux::Color* exr, int iWidth, int iHeight) {
		

		Scene s1;
		RenderSettings parm;
		parm.iWidth = iWidth;
		parm.iHeight = iHeight;
		float aspectRatio = 1.778;
		s1.createCam(lux::Vector(0.058, 3.004, 6.675), lux::Vector(0.007, -0.146, -0.989), lux::Vector(0.001, 0.989, -0.146), 54.00f, aspectRatio);
		testScene(s1);
		generateImage(s1, parm,exr);

		
	}
}