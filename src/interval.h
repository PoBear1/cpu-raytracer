#ifndef __PBRT_INTERVAL_H
#define __PBRT_INTERVAL_H
#include "floating_point.h"
class interval {
public:
	double min_v, max_v;
	interval() : min_v(+infinity), max_v(-infinity) {}
	interval(double min, double max) : min_v(min), max_v(max) {}
    double size() const {return max_v - min_v;}
    bool contains(double x) const {return min_v <= x && x <= max_v;}
    bool surrounds(double x) const {return min_v < x && x < max_v;}
	double clamp(double x) const {
		if(min_v > x) return min_v;
		if(max_v < x) return max_v;
		return x;
	}
	static const interval empty, universe;
};
const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
#endif