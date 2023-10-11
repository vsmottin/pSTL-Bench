#ifndef PSTL_BENCH_FOR_EACH_OMP_QUADRATIC_H
#define PSTL_BENCH_FOR_EACH_OMP_QUADRATIC_H

#include <algorithm>
#include <cmath>
#include <vector>

#include <omp.h>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace benchmark_for_each
{

	const auto for_each_omp_quadratic = [](auto && outerExecutionPolicy, auto && innerExecutionPolicy,
	                                       const auto & input_data, auto && f) {
		std::for_each(outerExecutionPolicy, input_data.begin(), input_data.end(), [&](const auto & e1) {
			std::for_each(innerExecutionPolicy, input_data.begin(), input_data.end(),
			              [&](const auto & e2) { f(e1, e2); });
		});
	};

}

#endif //PSTL_BENCH_FOR_EACH_OMP_QUADRATIC_H
