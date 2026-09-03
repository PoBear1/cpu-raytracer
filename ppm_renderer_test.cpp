#include <ppm_renderer.h>
#include <camera.h>
#include <colour.h>
#include <iostream>
#include <ray.h>
colour ray_colour(const ray& r) {
	vec3 dir = r.direction().unit();
	double a = (0.5 * dir[1] + 1.0);
    return (1 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}
int main() {
	int image_width = 7680;
	int image_height = 4320;
	ppm_renderer rend("image.ppm", image_width, image_height);
	camera cam(point3(0, 0, 0), image_width, image_height, 1.0, 2.0);
	for(int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
			ray pix_ray = cam.pixel_ray(i, j);
			rend.write_pixels({i, j}, ray_colour(pix_ray));
        }
    }
	std::clog << "\rDone.                 \n";
	return 0;
}