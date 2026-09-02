#include <ppm_renderer.h>
#include <iostream>
int main() {
	int image_width = 7680;
	int image_height = 4320;
	ppm_renderer rend("image.ppm", image_width, image_height);
	for(int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
            auto r = (double(i) / (image_width-1));
            auto b = (double(j) / (image_height-1)) * 1.0;
            auto g = (double(i) / (image_width-1));
			rend.write_pixels({i, j}, colour(r, g, b));
        }
    }
	std::clog << "\rDone.                 \n";
	return 0;
}