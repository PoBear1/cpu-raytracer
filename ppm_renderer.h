#ifndef __PBRT_PPM_RENDER
#define __PBRT_PPM_RENDER
#include <fstream>
#include <utility>
#include <string>
class ppm_renderer {
private:
	int image_width = 1920;
	int image_height = 512;
	const double max_rgb = 255.999;
	std::fstream output_image;
public:
	ppm_renderer(std::string filename, int image_w = 1920, int image_h = 512) : 
		image_width(image_w), 
		image_height(image_h) 
	{
		output_image = std::fstream(filename, std::ios::out | std::ios::trunc | std::ios::binary);
	}
	// void write_pixel(std::vector<std::pair<)

};
#endif