#ifndef __PBRT_RAY_TRACING_H
#define __PBRT_RAY_TRACING_H

#include <numbers>
#include <numeric>
#include <cmath>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = std::numbers::pi;

inline double deg_to_rad(double degrees) {
    return degrees * pi / 180.0;
}

#include "floating_point.h"
#include "hittable_list.h"
#include "ppm_renderer.h"
#include "hittable.h"
#include "sampling.h"
#include "vec_math.h"
#include "colour.h"
#include "camera.h"
#include "ray.h"

#include "objects/sphere.h"

#endif