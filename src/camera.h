#ifndef __PBRT_CAMERA_H
#define __PBRT_CAMERA_H
#include "floating_point.h"
#include "vec_math.h"
#include "ray.h"
class camera {
private:
	// camera positioning shenanigans
	point3 centre = point3(0.0, 0.0, 0.0);

	// image properties
	int image_width;
	int image_height;
	
	// optical properties
	double focal_length;
	double viewport_height;
	double viewport_width;

	// viewpoint direction and delta vectors
	vec3 viewport_u;
	vec3 viewport_v;
	vec3 pixel_du;
	vec3 pixel_dv;
	
	// upper-left pixel location
	point3 viewport_upper_left;
	point3 pixel00_loc;

	// sampling amounts
	int num_samples = 10;
	double sample_density = 1.0 / num_samples;
	int max_depth = 10;

	static colour ray_colour(const ray& r, const hittable_list& world, int depth) {
		if(depth <= 0) {return colour(0, 0, 0);}
		hit_record rec;
		interval ray_int(0.001, infinity);
		if(world.hit(r, ray_int, rec) && depth > 0) {
			ray scattered;
			colour atten;
			if(rec.mat -> scatter(r, rec, atten, scattered)) {
				return atten * ray_colour(scattered, world, depth - 1);
			}
			return colour(0, 0, 0);
		}
		vec3 dir = r.direction().unit();
		double a = (0.5 * dir[1] + 1.0);
		return (1 - a) * colour(1.0, 1.0, 1.0) + a * colour(0.5, 0.7, 1.0);
	}
public:
	constexpr camera(
		point3 centre, 
		int im_w, 
		int im_h, 
		double foc_len, 
		double view_h
	) : 
		centre(centre), 
		image_width(im_w),
		image_height(im_h),
		focal_length(foc_len),
		viewport_height(view_h),
		viewport_width(viewport_height * (static_cast<double>(image_width) / image_height)),
		viewport_u(vec3(viewport_width, 0, 0)),
		viewport_v(vec3(0, -viewport_height, 0)),
		pixel_du(viewport_u / image_width),
		pixel_dv(viewport_v / image_height),
		viewport_upper_left(centre - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2),
		pixel00_loc(viewport_upper_left + 0.5 * (pixel_du + pixel_dv))
	{}
	constexpr camera() : camera(point3(0, 0, 0), 1920, 1080, 1.0, 2.0) {};
	ray pixel_ray(int x_coord, int y_coord) const {
		vec2 sample = sample_square();
		point3 pixel_centre = pixel00_loc + ((x_coord + sample[0]) * pixel_du + (y_coord + sample[1]) * pixel_dv);
		vec3 ray_direction = pixel_centre - centre;
		return ray(centre, ray_direction);
	}
	vec2 sample_square() const {return vec2(random_double() - 0.5, random_double() - 0.5);}
	colour pixel_colour(int x_coord, int y_coord, const hittable_list& world) const {
		colour sampled_colour = colour(0, 0, 0);
		for(int sample = 0; sample < num_samples; ++sample) {
			ray pix_ray = pixel_ray(x_coord, y_coord);
			sampled_colour += ray_colour(pix_ray, world, max_depth);
		}
		sampled_colour = sampled_colour * sample_density;
		for(int i = 0; i < 3; ++i) {
			if(sampled_colour[i] > 0) sampled_colour[i] = std::sqrt(sampled_colour[i]);
		}
		return sampled_colour;
	}
};
#endif