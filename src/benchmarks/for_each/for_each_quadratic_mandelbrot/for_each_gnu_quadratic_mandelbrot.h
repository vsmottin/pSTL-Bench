
#ifndef PSTL_BENCH_FOR_EACH_GNU_QUADRATIC_MANDELBROT_H
#define PSTL_BENCH_FOR_EACH_GNU_QUADRATIC_MANDELBROT_H

#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

#include <benchmark_utils.h>

#include <omp.h>

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu_quadratic_mandelbrot = [](auto && outerExecutionPolicy, auto && innerExecutionPolicy,
	                                                  const auto & input_data, auto && quadratic_mandelbrot_kernel) {
		omp_set_nested(1);

		const auto width  = input_data.size();
		const auto heigth = input_data.size();

		constexpr auto x_start = -2.0;
		constexpr auto x_fin   = 1.0;
		constexpr auto y_start = -1.0;
		constexpr auto y_fin   = 1.0;

		const auto dx = (x_fin - x_start) / (width - 1);
		const auto dy = (y_fin - y_start) / (heigth - 1);

		// quite straight forward std::for_each. The body of the lambda has no intention behind it, the goal was just
		// to have a big enough computation that takes some amount of time.
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), [&](const auto & i) {
			// nested parallel loop with same strategy
			__gnu_parallel::for_each(input_data.begin(), input_data.end(), [&](const auto & j) {
				const auto x = x_start + j * dx; // current real value
				const auto y = y_fin - i * dy;   // current imaginary value

				auto value = quadratic_mandelbrot_kernel(x, y);

				benchmark::DoNotOptimize(value);
			});
		});
	};

}

#endif //PSTL_BENCH_FOR_EACH_GNU_QUADRATIC_MANDELBROT_H
