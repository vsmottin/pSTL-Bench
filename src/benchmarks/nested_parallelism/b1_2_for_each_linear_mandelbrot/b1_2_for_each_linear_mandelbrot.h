#ifndef PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_H
#define PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace B1 {

	const auto b1_2_for_each_linear_mandelbrot = [] (auto && policy,
													 const auto & pixel_x,
													 auto && mandelbrot) {
		const auto dx = (1.0 - -2.0) / (pixel_x.size() - 1);

		std::for_each(policy, pixel_x.begin(), pixel_x.end(), [&, dx] (const auto & entry) {
			auto val = mandelbrot(entry, dx);
#ifndef ONLY_GPU
			benchmark::DoNotOptimize(val);
#endif
		});

	};

}

#endif //PSTL_BENCH_B1_2_FOR_EACH_LINEAR_MANDELBROT_H
