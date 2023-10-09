#ifndef PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_OMP_H
#define PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_OMP_H

#ifdef USE_OMP

#include <vector>
#include <cmath>
#include <algorithm>

#include <omp.h>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace B1 {

	const auto b1_2_for_each_quadratic_omp = [] (auto && outerExecutionPolicy,
												 auto && innerExecutionPolicy,
												 const auto & input_data,
												 auto && f) {
		std::for_each(outerExecutionPolicy, input_data.begin(), input_data.end(), [&] (const auto & e1) {
			std::for_each(innerExecutionPolicy, input_data.begin(), input_data.end(), [&] (const auto & e2) {
				f(e1, e2);
			});
		});
	};

}

#endif // USE_OMP

#endif //PSTL_BENCH_B1_2_FOR_EACH_QUADRATIC_OMP_H
