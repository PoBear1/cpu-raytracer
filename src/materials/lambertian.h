#ifndef __PBRT_LAMBERTIAN_H
#define __PBRT_LAMBERTIAN_H
#include "../material_abs.h"
#include "../vec_math.h"
#include "../colour.h"
#include "../ray.h"
class lambertian : public material {
public:
	lambertian(const colour& albedo) : albedo(albedo) {}
	bool scatter(const ray& r_in, const hit_record& rec, colour& atten, ray& scattered) const override {
		vec3 scatter_dir = rec.normal + vec3::random_unit();
		if(near_zero(scatter_dir)) {scatter_dir = rec.normal;}
		scattered = ray(rec.p, scatter_dir);
		atten = albedo;
		return true;
	}
private:
	colour albedo;
};
#endif