#include "Engine.h"
#include "OpenImageIO/imageio.h"
#include "RenderSettings.h"
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
	//vol::printMessage();
	lux::Color* exr = new lux::Color[IWIDTH*IHEIGHT];
	vol::Engine e;
	RenderSettings rend;
	rend.iWidth = IWIDTH;
	rend.iHeight = IHEIGHT;
	e.setRenderSettings(rend);
	e.render(exr);
	writeOIIOImage("D:/Work/soum.exr", exr);
	std::cin.get();
}