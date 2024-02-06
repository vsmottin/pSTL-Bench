#ifndef PSTL_BENCH_COUNT_IF_GNU_H
#define PSTL_BENCH_COUNT_IF_GNU_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/algorithm>

namespace benchmark_count_if
{
	const auto count_if_gnu = [](auto && policy, const auto & container, auto & condition) {
		return __gnu_parallel::count_if(container.begin(), container.end(), condition);
	};
}

#endif //PSTL_BENCH_COUNT_IF_GNU_H
