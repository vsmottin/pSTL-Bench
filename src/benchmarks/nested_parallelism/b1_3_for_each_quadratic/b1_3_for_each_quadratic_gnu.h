#ifndef PSTL_BENCH_B1_3_FOR_EACH_QUADRATIC_GNU_H
#define PSTL_BENCH_B1_3_FOR_EACH_QUADRATIC_GNU_H

#include <vector>
#include <cmath>
#include <algorithm>

#include <omp.h>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <parallel/algorithm>

namespace B1 {

	const auto b1_3_for_each_quadratic_gnu = [] (auto && outerExecutionPolicy,
												 auto && innerExecutionPolicy,
												 const auto & input_data,
												 auto && f) {
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), [&] (const auto & e1) {
			__gnu_parallel::for_each(input_data.begin(), input_data.end(), [&] (const auto & e2) {
				f(e1, e2);
			});
		});
	};

}


#endif //PSTL_BENCH_B1_3_FOR_EACH_QUADRATIC_GNU_H
