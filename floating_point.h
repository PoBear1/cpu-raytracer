#ifndef __PBRT_FLOATING_POINT
#define __PBRT_FLOATING_POINT
#include <type_traits>
#include <concepts>
#include <numeric>
static constexpr double one_min_eps = 0x1.fffffffffffffp-1;
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
	typename T_int = std::conditional_t<std::is_same_v<T, float>, uint32_t, uint64_t>;
	T_int ui = std::bit_cast<T_int>(v);
	if(v >= 0.0) {++ui;} else {--ui;}
	return std::bit_cast<T>(ui); 
}
#endif