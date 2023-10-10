#ifndef PSTL_BENCH_REDUCE_OMP_H
#define PSTL_BENCH_REDUCE_OMP_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include "omp_helpers.h"

namespace benchmark_reduce
{
	const auto reduce_omp = [](auto && policy, const auto & container) {
		return omp::reduce(policy, container.begin(), container.end(), 0);
	};
}

#endif //PSTL_BENCH_REDUCE_OMP_H
