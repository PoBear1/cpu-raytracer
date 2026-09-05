#include <src/ray_tracing.h>
#include <iostream>
#include <thread>

int main() {
	int image_width = 7680;
	int image_height = 4320;
	// int image_width = 640;
	// int image_height = 360;
	hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1.2), 0.5, std::make_shared<lambertian>(colour(0.1, 0.2, 0.5))));
    world.add(std::make_shared<sphere>(point3(1, 0, -1), 0.5, std::make_shared<metal>(colour(0.8, 0.8, 0.8), 0.1)));
    world.add(std::make_shared<sphere>(point3(-1, 0, -1), 0.5, std::make_shared<dielectric>(1.00 / 1.33)));
    world.add(std::make_shared<sphere>(point3(-1, 0, -1), 0.3, std::make_shared<dielectric>(1.33 / 1.00)));
    world.add(std::make_shared<sphere>(point3(0, -100.5, -1), 100, std::make_shared<lambertian>(colour(0.8, 0.8, 0.0))));
	ppm_renderer rend("image", image_width, image_height);
	camera cam(point3(0, 0, 0), image_width, image_height, 1.0, 2.0);
	for(int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
			colour sampled_colour = cam.pixel_colour(i, j, world);
			rend.write_pixels({i, j}, sampled_colour);
        }
    }
	std::clog << "\rDone.                 \n";
	return 0;
}