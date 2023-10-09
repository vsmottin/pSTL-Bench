#ifndef PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_H
#define PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_H

#include <vector>
#include <cmath>
#include <algorithm>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace B1 {

	const auto b1_2_for_each_linear_mandelbrot_omp = [] (auto && policy,
														 const auto & pixel_x,
														 auto && mandelbrot_kernel) {

		// calculating the 17 row of mandelbrot with an adjustable limit.
		// adjusted from https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc

		const auto dx = (1.0 - -2.0) / (pixel_x.size() - 1);

		omp::for_each(policy, pixel_x.begin(), pixel_x.end(), [&, dx] (const auto & entry) {
			auto val = mandelbrot_kernel(entry, dx);
			benchmark::DoNotOptimize(val);
		});

	};

}

#endif //PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_OMP_H
