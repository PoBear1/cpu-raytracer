#ifndef __PBRT_FLOATING_POINT_H
#define __PBRT_FLOATING_POINT_H
#include <type_traits>
#include <concepts>
#include <numeric>
static constexpr double one_min_eps = 0x1.fffffffffffffp-1;
template<typename T> 
inline bool is_nan(T x) requires std::floating_point<T> {return std::isnan(x);}
template<typename T>
inline bool is_nan(T x) requires std::integral<T> {return false;}
template<typename T> 
inline bool is_inf(T x) requires std::floating_point<T> {return std::isinf(x);}
template<typename T>
inline bool is_inf(T x) requires std::integral<T> {return false;}
template<typename T>
inline bool is_finite(T x) requires std::floating_point<T> {return std::isfinite(x);}
template<typename T>
inline bool is_finite(T x) requires std::integral<T> {return true;}
template<typename T>
inline T next_num_up(T v) requires std::floating_point<T> {
	if(is_inf(v) && v > 0.0) {return v;}
	if(v == -0.0) {return 0.0;}
	using T_int = std::conditional_t<std::is_same_v<T, float>, uint32_t, uint64_t>;
	T_int ui = std::bit_cast<T_int>(v);
	if(v >= 0.0) {++ui;} else {--ui;}
	return std::bit_cast<T>(ui); 
}

#include <numbers>
#include <numeric>
#include <cmath>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = std::numbers::pi;

inline double deg_to_rad(double degrees) {
    return degrees * pi / 180.0;
}

#include <cstdlib>

inline double random_double() {return std::rand() / (RAND_MAX + 1.0);}
inline double random_double(double min, double max) {return min + (max - min) * random_double();}

#endif