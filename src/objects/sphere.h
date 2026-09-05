#ifndef __PBRT_SPHERE_H
#define __PBRT_SPHERE_H
#include "../material_abs.h"
#include "../hittable.h"
#include "../interval.h"
#include "../vec_math.h"
class sphere : public hittable {
private:
	point3 centre;
	double radius;
	std::shared_ptr<material> mat;
public:
	sphere(const point3& centre, double radius, std::shared_ptr<material> mat) : centre(centre), radius(std::fmax(0, radius)), mat(mat) {}
	bool hit(const ray& r, interval t, hit_record& rec) const override {
		vec3 oc = centre - r.origin();
		double a = r.direction().norm();
		double h = dot(r.direction(), oc);
		double c = oc.norm() - radius * radius;
		double disc = h * h - a * c;
		if(disc < 0) {return false;}
		double disc_sqrt = std::sqrt(disc);
		double root = (h - disc_sqrt) / a;
		if(!t.contains(root)) {
			root = (h + disc_sqrt) / a;
			if(!t.contains(root)) {return false;}
		}
		rec.t = root;
		rec.p = r.at(rec.t);
		rec.mat = mat;
		vec3 outward_normal = (rec.p - centre) / radius;
		rec.set_face_normal(r, outward_normal);
		return true;
	}
};
#endif