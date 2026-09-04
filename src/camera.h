#ifndef __PBRT_CAMERA_H
#define __PBRT_CAMERA_H
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
		point3 pixel_centre = pixel00_loc + (x_coord * pixel_du + y_coord * pixel_dv);
		vec3 ray_direction = pixel_centre - centre;
		return ray(pixel_centre, ray_direction);
	}
};
#endif