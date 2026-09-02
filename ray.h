#ifndef __PBRT_RAY_H
#define __PBRT_RAY_H
#include <vec_math.h>
using point3 = vec<double, 3>;
using vec3 = vec<double, 3>;
class ray {
private:
	point3 orig;
	vec3 dir;
public:
	constexpr ray() = default;
	constexpr ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
};
#endif