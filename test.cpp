#include <src/ray_tracing.h>
#include <iostream>

colour ray_colour(const ray& r, const hittable_list& world) {
	hit_record rec;
	if(world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + colour(1, 1, 1));
	}
	vec3 dir = r.direction().unit();
	double a = (0.5 * dir[1] + 1.0);
    return (1 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
}
int main() {
	int image_width = 7680;
	int image_height = 4320;
	// int image_width = 640;
	// int image_height = 360;
	hittable_list world;
    world.add(std::make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(point3(0, -102, -1), 100));
	ppm_renderer rend("image", image_width, image_height);
	camera cam(point3(0, 0, 0), image_width, image_height, 1.0, 2.0);
	for(int j = 0; j < image_height; j++) {
		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; i++) {
			ray pix_ray = cam.pixel_ray(i, j);
			rend.write_pixels({i, j}, ray_colour(pix_ray, world));
        }
    }
	std::clog << "\rDone.                 \n";
	return 0;
}