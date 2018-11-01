#include "Engine.h"
#include "OpenImageIO/imageio.h"
#include "RenderSettings.h"
#include <chrono>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <windows.h>
#include <omp.h>
/*
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
*/
OIIO_NAMESPACE_USING


#define IWIDTH 480  //480
#define IHEIGHT 270 //270

namespace fs = boost::filesystem;

static std::string getexepath()
{
	char result[MAX_PATH];
	return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
}

void writeOIIOImage(const char* fname, lux::Color* exr)
{
	std::cout << "WRITING" << std::endl;

	float* pixels = new float[4 *IWIDTH*IHEIGHT];
	int index = 0;
	for (int j = 0; j < IHEIGHT; j++)
	{
		for (int i = 0; i < IWIDTH; i++)
		{
			for (int c = 0; c < 4; c++)
			{
				pixels[(i + IWIDTH * (IHEIGHT - j - 1)) * 4 + 0] = exr[i + (IWIDTH*j)].X();
				pixels[(i + IWIDTH * (IHEIGHT - j - 1)) * 4 + 1] = exr[i + (IWIDTH*j)].Y();
				pixels[(i + IWIDTH * (IHEIGHT - j - 1)) * 4 + 2] = exr[i + (IWIDTH*j)].Z();
				pixels[(i + IWIDTH * (IHEIGHT - j - 1)) * 4 + 3] = exr[i + (IWIDTH*j)].W();
			}
		}
	}
	
	ImageOutput::unique_ptr out = ImageOutput::create(std::string(fname));
	if (!out)
	{
		std::cout << "Not able to write an image to file" << fname << std::endl;
	}
	else
	{
		ImageSpec spec(IWIDTH, IHEIGHT, 4, TypeDesc::FLOAT);
		spec.attribute("user", "soumitragoswami");
		spec.attribute("writer", "writeOIIOImage");
		out->open(fname, spec);
		out->write_image(TypeDesc::FLOAT, pixels);
		out->close();
	}
	delete[] pixels;
	std::cout << "FINISHED WRITING TO " << fname << std::endl;
	out->destroy;
}

int main()
{
	using namespace std::chrono;
	//vol::printMessage();

	vol::Engine e;
	RenderSettings rend;
	rend.iWidth = IWIDTH;
	rend.iHeight = IHEIGHT;
	e.setRenderSettings(rend);

	fs::path p1 = getexepath();
	p1 = p1.parent_path();
	//std::cout << "Current EXE Directory: " << p1 << std::endl;
	if (fs::exists(p1)) {
		fs::path dir = p1.string() + "/MapData";
		if (!fs::is_directory(dir)) {
			fs::create_directory(dir);
			std::cout << "Directory doesn't exist. Directory created at " << dir.string() << std::endl;
		}
		else 
			std::cout << "Using Directory " << dir.string() << std::endl;
		
		rend.mapDir = dir.string();

		if (rend.renderDir.length() == 0) {
			fs::path rDir = p1.string() + "/Render";
			if (!fs::is_directory(rDir)) {
				fs::create_directory(rDir);
				std::cout << "Rendering Directory doesn't exist. Directory created at " << rDir.string() << std::endl;
			}
			else
				std::cout << "Using Rendering Directory " << rDir.string() << std::endl;
			rend.renderDir = rDir.string();
		}
	}
	else {
		std::cout << "No valid path for directory to save data" << std::endl;
			return 0;
	}

	
	for (int f = rend.fBegin; f < (rend.fEnd + 1); f += rend.fInc)
	{
		auto start = high_resolution_clock::now();
		std::cout << "RENDERING BEGIN" << std::endl;
		std::cout << "Frame " << f << std::endl;
		lux::Color* exr = new lux::Color[IWIDTH*IHEIGHT];
		e.render(exr,f);
		std::cout << "RENDERING END" << std::endl;
		boost::format fmt(".%04d.exr");
		fmt % f;
		std::string fName = rend.renderDir + "/" + rend.fileName + fmt.str();
		const char* c = fName.c_str();
		writeOIIOImage(c, exr);
		auto stop = high_resolution_clock::now();
		auto timeTaken = duration_cast<seconds>(stop - start);
		std::cout << "Time Elapsed: " << int(timeTaken.count()/3600) << "hr: " << int(timeTaken.count()/60)%60 << "min: " << int (timeTaken.count())%60 << "sec" << std::endl;

		delete[] exr;

		
	}
	
	std::cin.get();
	//_CrtDumpMemoryLeaks();
	return 0;
}