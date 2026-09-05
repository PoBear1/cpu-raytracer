#ifndef __PBRT_MATERIAL_ABS_H
#define __PBRT_MATERIAL_ABS_H
#include "hittable.h"
#include "colour.h"
class material {
public:
	virtual ~material() = default;
	virtual bool scatter(
		const ray& r, const hit_record& rec, colour& atten, ray& scattered
	) const {
		return false;
	}
};
#endif