
#ifndef PSTL_BENCH_B1_1_FOR_EACH_LINEAR_OMP_H
#define PSTL_BENCH_B1_1_FOR_EACH_LINEAR_OMP_H

#include <vector>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace B1 {

	const auto b1_1_for_each_linear_omp = [] (auto && policy,
											  const auto & input_data,
											  auto && f) {
		omp::for_each(policy, input_data.begin(), input_data.end(), f);
	};

}

#endif //PSTL_BENCH_B1_1_FOR_EACH_LINEAR_OMP_H
