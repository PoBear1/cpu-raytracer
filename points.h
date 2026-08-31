#ifndef __PBRT_POINT_H
#define __PBRT_POINT_H
#include <floating_point.h>
#include <cassert>
#define PBRT_DEBUG 1
#if PBRT_DEBUG == 1
	#define DCHECK(x) assert(x)
#endif
template<template<typename> class Child, typename T>
class tuple2 {
public:
	static const int n_dims = 2;
	tuple2() = default;
	tuple2(T x, T y) : x(x), y(y) {DCHECK(!has_nan());}
	bool has_nan() const {return is_nan(x) || is_nan(y);}
	#if PBRT_DEBUG == 1
		tuple2(Child<T> c) {
			DCHECK(!c.has_nan());
			x = c.x;
			y = c.y;
		}
		Child<T> operator=(Child<T> c) {
			DCHECK(!c.has_nan());
			x = c.x;
			y = c.y;
			return static_cast<Child<T>&>(*this);
		}
	#endif
	T x{}, y{};
};
#endif