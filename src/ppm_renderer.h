#ifndef __PBRT_PPM_RENDER
#define __PBRT_PPM_RENDER
#include "colour.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
class ppm_renderer {
private:
	int image_width = 1920;
	int image_height = 1080;
	const double max_rgb = 255.999;
	std::string f_name;
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
	ppm_renderer(std::string filename, int image_w = 7680, int image_h = 4320) : 
		image_width(image_w), 
		image_height(image_h),
		f_name(filename)
	{
		output_image = std::fstream(filename + ".ppm", std::ios::out | std::ios::trunc | std::ios::binary);
		std::string header = std::format("P6\n{} {}\n{}\n", image_width, image_height, static_cast<int>(max_rgb));
		output_image.write(header.c_str(), static_cast<long long>(header.length()));
		data_start = static_cast<std::streamoff>(header.length());
		for(int i = 0; i < image_width * image_height; ++i) {
			output_image.write("\x00\x00\x00", 3);
		}
	}
	~ppm_renderer() {
		std::string command_magick = "magick " + f_name + ".ppm " + f_name + ".png";
		std::string command_rm = "rm -rf " + f_name + ".ppm";
		int res_magick = std::system(command_magick.c_str());
		if(res_magick != -1) {
			std::clog << "Successfully converted " << f_name << ".ppm!" << std::endl;
		} else {
			std::clog << "Error occured when trying to convert " << f_name << ".ppm!" << std::endl;
		}
		int res_rm = std::system(command_rm.c_str());
		if(res_rm != -1) {
			std::clog << "Successfully deleted " << f_name << ".ppm!" << std::endl;
		} else {
			std::clog << "Error occured when trying to delete " << f_name << ".ppm!" << std::endl;
		}
	}
	void write_pixels(std::pair<int, int> coord, colour pixel) {
		write_pixel(coord.first, coord.second, pixel);
		if(++num_buffered >= buf_max) {
			output_image.flush();
			num_buffered = 0;
		}
	}
	void write_pixels(std::vector<std::pair<std::pair<int, int>, colour>> pixels) {
		for(auto [coords, pixel]: pixels) {
			auto [x, y] = coords;
			write_pixel(x, y, pixel);
			if(++num_buffered >= buf_max) {
				output_image.flush();
				num_buffered = 0;
			}
		}
	}
};
#endif