#ifndef PSTL_BENCH_FOR_EACH_GNU_LINEAR_MANDELBROT_H
#define PSTL_BENCH_FOR_EACH_GNU_LINEAR_MANDELBROT_H

#include <algorithm>
#include <cmath>
#include <vector>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu_linear_mandelbrot = [](auto && policy, const auto & pixel_x, auto && mandelbrot_kernel) {
		// calculating the 17 row of mandelbrot with an adjustable limit.
		// adjusted from https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc

		const auto dx = (1.0 - -2.0) / (pixel_x.size() - 1);

		__gnu_parallel::for_each(pixel_x.begin(), pixel_x.end(), [&, dx](const auto & entry) {
			auto val = mandelbrot_kernel(entry, dx);
			benchmark::DoNotOptimize(val);
		});
	};

}

#endif //PSTL_BENCH_FOR_EACH_GNU_LINEAR_MANDELBROT_H
