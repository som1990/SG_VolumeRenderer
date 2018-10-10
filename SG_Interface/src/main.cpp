#include "Engine.h"
#include "OpenImageIO/imageio.h"
#include "RenderSettings.h"
#include <chrono>
OIIO_NAMESPACE_USING


#define IWIDTH 480  //480
#define IHEIGHT 270 //270

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
	
	for (int f = rend.fBegin; f < (rend.fEnd + 1); f += rend.fInc)
	{
		auto start = high_resolution_clock::now();
		std::cout << "RENDERING BEGIN" << std::endl;
		std::cout << "Frame " << f << std::endl;
		lux::Color* exr = new lux::Color[IWIDTH*IHEIGHT];
		e.render(exr,f);
		std::cout << "RENDERING END" << std::endl;
		writeOIIOImage("D:/Work/soum.exr", exr);
		auto stop = high_resolution_clock::now();
		auto timeTaken = duration_cast<seconds>(stop - start);
		std::cout << "Time Elapsed: " << int(timeTaken.count()/3600) << "hr: " << int(timeTaken.count()/60)%60 << "min: " << int (timeTaken.count())%60 << "sec" << std::endl;

		delete[] exr;
		
	}

	std::cin.get();
}