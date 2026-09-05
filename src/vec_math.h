#ifndef __PBRT_VEC_MATH_H
#define __PBRT_VEC_MATH_H
#include "floating_point.h"
#include <cassert>
#include <cmath>
#include <array>
#define PBRT_DEBUG 1
#if PBRT_DEBUG == 1
	#define DCHECK(x) assert(x)
#else
	#define DCHECK(x) (x)
#endif
template<typename T, size_t N>
class vec {
	std::array<T, N> data{};
	// this looks so cursed lmfao
	template<typename F, size_t... I>
	static constexpr vec apply_binary(F f, const vec& a, const vec& b, std::index_sequence<I...>) {return vec{f(a[I], b[I])...};}
	template<typename F, size_t... I>
	static constexpr vec apply_unary(F f, const vec& a, std::index_sequence<I...>) {return vec{f(a[I])...};}
	template<typename F, size_t... I>
	constexpr void apply_binary(F f, const vec& b, std::index_sequence<I...>) {((data[I] = f(data[I], b[I])), ...);}
	template<typename F, typename G, size_t... I>
	static constexpr T fold_binary(F f, G g, T acc, const vec& a, const vec& b, std::index_sequence<I...>) {((acc = f(acc, g(a[I], b[I]))), ...); return acc;}
	template<typename Acc, typename F, typename G, size_t... I>
	static constexpr Acc fold_unary(F f, G g, Acc acc, const vec& a, std::index_sequence<I...>) {((acc = f(acc, g(a[I]))), ...); return acc;}
	template<typename F, size_t... I>
	static constexpr void generate(F f, vec& a, std::index_sequence<I...>) {((a[I] = f()), ...);}
public:
	constexpr vec() = default;
	template<typename... Args> requires (sizeof...(Args) == N)
	constexpr vec(Args... args) : data{static_cast<T>(args)...} {
		DCHECK((is_finite(args) && ...));
	}
	// access operators
	constexpr T& operator[](size_t i) {return data[i];}
	constexpr const T& operator[](size_t i) const {return data[i];}
	// math operators
	friend constexpr vec operator+(const vec& a, const vec& b) {
		return apply_binary([](T x, T y) -> T {return x + y;}, a, b, std::make_index_sequence<N>{});
	}
	constexpr vec& operator+=(const vec &b) {
		apply_binary([](T x, T y) -> T {return x + y;}, b, std::make_index_sequence<N>{});	
		return *this;
	}
	friend constexpr vec operator*(const vec& a, const vec& b) {
		return apply_binary([](T x, T y) -> T {return x * y;}, a, b, std::make_index_sequence<N>{});
	}
	constexpr vec& operator*=(const vec &b) {
		apply_binary([](T x, T y) -> T {return x * y;}, b, std::make_index_sequence<N>{});	
		return *this;
	}
	friend constexpr vec operator*(const T& a, const vec& b) {
		return apply_unary([&a](T x) -> T {return a * x;}, b, std::make_index_sequence<N>{});
	}
	friend constexpr vec operator*(const vec& b, const T& a) {
		return apply_unary([&a](T x) -> T {return a * x;}, b, std::make_index_sequence<N>{});
	}
	friend constexpr vec operator/(const vec& b, const T& a) {
		DCHECK(a != 0);
		return (1 / a) * b;
	}
	friend constexpr vec operator-(const vec& a, const vec& b) {
		return apply_binary([](T x, T y) -> T {return x - y;}, a, b, std::make_index_sequence<N>{});
	}
	constexpr vec& operator-=(const vec &b) {
		apply_binary([](T x, T y) -> T {return x - y;}, b, std::make_index_sequence<N>{});	
		return *this;
	}
	friend constexpr vec operator-(const vec& a) {
		return apply_unary([](T x) -> T {return -x;}, a, std::make_index_sequence<N>{});
	}
	friend constexpr T dot(const vec& a, const vec& b) {
		return fold_binary([](T x, T y) -> T {return x + y;}, [](T x, T y) -> T {return x * y;}, T{0}, a, b, std::make_index_sequence<N>{});
	}
	friend T distance(const vec& a, const vec& b) {
		vec c = a - b;
		return std::sqrt(dot(c, c));
	}
	T norm() const {return dot(*this, *this);}
	T length() const {return std::sqrt(dot(*this, *this));}
	vec unit() const {return *this / length();}
	friend constexpr bool near_zero(const vec& a) {
		double s = 1e-10;
		bool near_z = true;
		return fold_unary(
			[](bool a, bool b) -> bool {return a && b;}, 
			[s](double x) -> bool {return std::abs(x) < s;},
			near_z, a, std::make_index_sequence<N>{}
		);
	}
	static vec random() {
		vec new_vec;
		generate([]() -> double {return random_double();}, new_vec, std::make_index_sequence<N>{});
		return new_vec;
	}
	static vec random(double min_v, double max_v) {
		vec new_vec;
		generate([min_v, max_v]() -> double {return random_double(min_v, max_v);}, new_vec, std::make_index_sequence<N>{});
		return new_vec;
	}
	static vec random_unit() {
		vec new_vec;
		while(true) {
			new_vec = random(-1, 1);
			double len = new_vec.norm();
			if(len <= 1 && len > 1e-160) {return new_vec.unit();}
		}
	}
	static vec random_on_hemisphere(const vec& normal) {
		vec rand_unit = random_unit();
		if(dot(normal, rand_unit) > 0) {
			return rand_unit;
		} else {
			return -rand_unit;
		}
	}
};
// special cross product because ewwww
template<typename T, size_t N> requires (N == 3)
constexpr vec<T, N> cross(const vec<T, N>& a, const vec<T, N>& b) {
	return vec<T, N>(
		a[1] * b[2] - a[2] * b[1], 
		a[2] * b[0] - a[0] * b[2], 
		a[0] * b[1] - a[1] * b[0]
	);
}
template<typename T, size_t N>
constexpr vec<T, N> reflect(const vec<T, N>& v, const vec<T, N>& n) {
	return v - 2 * dot(v, n) * n;
}
template<typename T, size_t N>
constexpr vec<T, N> refract(const vec<T, N>& uv, const vec<T, N>& n, double etai_on_etat) {
	double cos_theta = std::fmin(1.0, dot(-uv, n));
	vec<T, N> r_out_perp = etai_on_etat * (uv + cos_theta * n);
	vec<T, N> r_out_para = -std::sqrt(std::fabs(1.0 - r_out_perp.norm())) * n;
	return r_out_para + r_out_perp;
}
using point3 = vec<double, 3>;
using vec3 = vec<double, 3>;
using point2 = vec<double, 2>;
using vec2 = vec<double, 2>;
#endif