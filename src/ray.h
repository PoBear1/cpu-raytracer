#ifndef __PBRT_RAY_H
#define __PBRT_RAY_H
#include "vec_math.h"
class ray {
private:
	point3 orig;
	vec3 dir;
public:
	constexpr ray() = default;
	constexpr ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
	constexpr const point3& origin() const {return orig;}
	constexpr const vec3& direction() const {return dir;}
	constexpr point3 at(const double t) const {return orig + t * dir;}
};
#endif