#ifndef __PBRT_SAMPLING_H
#define __PBRT_SAMPLING_H
#include "floating_point.h"
#include <numeric>
#include <vector>
#include <cmath>
#include <span>
double balance_heuristic(int nf, double f_pdf, int ng, double g_pdf) {return (nf * f_pdf) / (nf * f_pdf + ng * g_pdf);}
double power_heuristic(int nf, double f_pdf, int ng, double g_pdf) {return std::sqrt(nf * f_pdf) / (std::sqrt(nf * f_pdf) + std::sqrt(ng * g_pdf));}
int sample_discrete(std::span<const double> weights, double u, double *pmf, double *u_remapped) {
	if(weights.empty()) {
		if(pmf) *pmf = 0;
		return -1;
	}
	double sum_weights = std::accumulate(weights.begin(), weights.end(), 0.0), up = u * sum_weights;
	if(up == sum_weights) {
		up = next_num_up(up);
	}
	int offset = 0;
	double sum = 0.0;
	while(sum + weights[offset] <= up) {sum += weights[offset++];}
	if(pmf) {*pmf = weights[offset] / sum_weights;}
	if(u_remapped) {*u_remapped = std::min((up - sum) / weights[offset], one_min_eps);}
	return offset;
}
inline double l_erp(double x, double a, double b) {return (1 - x) * a + x * b;}
inline double lin_pdf(double x, double a, double b) {
	if(x < 0 || x > 1) return 0;
	return 2 * l_erp(x, a, b) / (a + b);
}
double sample_lin(double u, double a, double b) {
	if(u == 0 && a == 0) return 0;
	double x = u * (a + b) / (a + std::sqrt(l_erp(u, a * a, b * b)));
	return std::min(x, one_min_eps);
}
inline double invert_lin_pdf(double x, double a, double b) {return x * (a * (2 - x) + b * x) / (a + b);}
// double bilinear_pdf()
#endif