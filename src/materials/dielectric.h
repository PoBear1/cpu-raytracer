#ifndef __PBRT_DIELECTRIC_H
#define __PBRT_DIELECTRIC_H
#include "../material_abs.h"
#include "../vec_math.h"
#include "../colour.h"
#include "../ray.h"
class dielectric : public material {
public:
	dielectric(double refract_index) : refract_index(refract_index) {}
	bool scatter(const ray& r_in, const hit_record& rec, colour& atten, ray& scattered) const override {
		atten = colour(1, 1, 1);
		double ri = rec.front_face ? 1.0 / refract_index : refract_index;
		vec3 dir = r_in.direction().unit(), direction;
		double cos_theta = std::fmin(dot(-dir, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
		if(ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double()) {
			direction = reflect(dir, rec.normal);
		} else {
			direction = refract(dir, rec.normal, ri);
		}
		scattered = ray(rec.p, direction);
		return true;
	}
private:
	double refract_index;
	static double reflectance(double cosine, double reflectance_index) {
		double r0 = (1 - reflectance_index) / (1 + reflectance_index);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cosine), 5);
	}
};
#endif