#ifndef __PBRT_SPHERE_H
#define __PBRT_SPHERE_H
#include "../hittable.h"
#include "../vec_math.h"
class sphere : public hittable {
private:
	point3 centre;
	double radius;
public:
	sphere(const point3& centre, double radius) : centre(centre), radius(std::fmax(0, radius)) {}
	bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
		vec3 oc = centre - r.origin();
		double a = r.direction().norm();
		double h = dot(r.direction(), oc);
		double c = oc.norm() - radius * radius;
		double disc = h * h - a * c;
		if(disc < 0) return false;
		double disc_sqrt = std::sqrt(disc);
		double root = (h - disc_sqrt) / a;
		if(root <= ray_tmin || ray_tmax <= root) {
			root = (h + disc_sqrt) / a;
			if(root <= ray_tmin || ray_tmax <= root) return false;
		}
		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - centre) / radius;
		rec.set_face_normal(r, outward_normal);
		return true;
	}
};
#endif