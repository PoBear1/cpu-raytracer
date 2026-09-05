#ifndef __PBRT_HITTABLE_H
#define __PBRT_HITTABLE_H
#include "interval.h"
#include "vec_math.h"
#include "ray.h"
class material;
struct hit_record {
public:
	point3 p;
	vec3 normal;
	double t;
	bool front_face;
	std::shared_ptr<material> mat;
	void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
		normal = normal.unit();
	}
};
class hittable {
public:
	virtual ~hittable() = default;
	virtual bool hit(const ray& r, interval t, hit_record& rec) const = 0;
};
#endif