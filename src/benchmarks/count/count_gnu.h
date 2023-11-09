#ifndef PSTL_BENCH_COUNT_GNU_H
#define PSTL_BENCH_COUNT_GNU_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/algorithm>

namespace benchmark_count
{
	const auto count_gnu = [](auto && policy, const auto & container, const auto & value) {
		return __gnu_parallel::count(container.begin(), container.end(), value);
	};
}

#endif //PSTL_BENCH_COUNT_GNU_H
