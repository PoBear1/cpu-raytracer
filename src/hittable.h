#ifndef __PBRT_HITTABLE_H
#define __PBRT_HITTABLE_H
#include "vec_math.h"
#include "ray.h"
struct hit_record {
public:
	point3 p;
	vec3 normal;
	double t;
};
class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
#endif