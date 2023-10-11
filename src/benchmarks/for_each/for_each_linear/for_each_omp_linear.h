
#ifndef PSTL_BENCH_FOR_EACH_OMP_LINEAR_H
#define PSTL_BENCH_FOR_EACH_OMP_LINEAR_H

#include <vector>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace benchmark_for_each
{

	const auto for_each_omp_linear = [](auto && policy, const auto & input_data, auto && f) {
		omp::for_each(policy, input_data.begin(), input_data.end(), f);
	};

}

#endif //PSTL_BENCH_FOR_EACH_OMP_LINEAR_H
