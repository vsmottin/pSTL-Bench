#ifndef PSTL_BENCH_FOR_EACH_STD_LINEAR_MANDELBROT_H
#define PSTL_BENCH_FOR_EACH_STD_LINEAR_MANDELBROT_H


#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

#include <benchmark_utils.h>

namespace benchmark_for_each
{

	const auto for_each_std_linear_mandelbrot = [](auto && policy, const auto & pixel_x, auto && mandelbrot) {
		const auto dx = (1.0 - -2.0) / (pixel_x.size() - 1);

		std::for_each(policy, pixel_x.begin(), pixel_x.end(), [&, dx](const auto & entry) {
			auto val = mandelbrot(entry, dx);
#ifndef ONLY_GPU
			benchmark::DoNotOptimize(val);
#endif
		});
	};

} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_STD_LINEAR_MANDELBROT_H
