#ifndef __PBRT_METAL_H
#define __PBRT_METAL_H
#include "../material_abs.h"
#include "../vec_math.h"
#include "../colour.h"
#include "../ray.h"
class metal : public material {
public:
	metal(const colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
	bool scatter(const ray& r_in, const hit_record& rec, colour& atten, ray& scattered) const override {
		vec3 scatter_dir = reflect(r_in.direction(), rec.normal).unit() + fuzz * vec3::random_unit();
		scattered = ray(rec.p, scatter_dir);
		atten = albedo;
		return true;
	}
private:
	colour albedo;
	double fuzz;
};
#endif