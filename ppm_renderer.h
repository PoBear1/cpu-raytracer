#ifndef __PBRT_PPM_RENDER
#define __PBRT_PPM_RENDER
#include <colour.h>
#include <fstream>
#include <utility>
#include <string>
class ppm_renderer {
private:
	int image_width = 1920;
	int image_height = 512;
	const double max_rgb = 255.999;
	std::fstream output_image;
	int num_buffered = 0;
	const int buf_max = 1000;
	std::streampos data_start;
	void write_pixel(int x, int y, colour pixel_col) {
		std::streamoff offset = data_start + std::streamoff(3 * (x + y * image_width));
		output_image.seekp(offset);
		unsigned char rgb[3] = {
			(unsigned char)(pixel_col[0] * max_rgb), 
			(unsigned char)(pixel_col[1] * max_rgb), 
			(unsigned char)(pixel_col[2] * max_rgb)
		};
		output_image.write(reinterpret_cast<char*>(rgb), 3);
	}
public:
	ppm_renderer(std::string filename, int image_w = 1920, int image_h = 512) : 
		image_width(image_w), 
		image_height(image_h) 
	{
		output_image = std::fstream(filename, std::ios::out | std::ios::trunc | std::ios::binary);
		std::string header = std::format("P6\n{} {}\n{}\n", image_width, image_height, static_cast<int>(max_rgb));
		output_image.write(header.c_str(), static_cast<long long>(header.length()));
		data_start = output_image.tellp();
		output_image.write("\x00\x00\x00", 3);
	}
	void write_pixels(std::vector<std::pair<std::pair<int, int>, colour>> pixels) {

	}
};
#endif