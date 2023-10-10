#ifndef PSTL_BENCH_COUNT_IF_OMP_H
#define PSTL_BENCH_COUNT_IF_OMP_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include "omp_helpers.h"

namespace benchmark_count_if
{
	const auto count_if_omp = [](auto && policy, const auto & container, auto & condition) {
		return omp::count_if(policy, container.begin(), container.end(), condition);
	};
}

#endif //PSTL_BENCH_COUNT_IF_OMP_H
