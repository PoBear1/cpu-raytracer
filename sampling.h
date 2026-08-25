#ifndef __PBRT_SAMPLING_H
#define __PBRT_SAMPLING_H
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
		
	}

}
#endif
