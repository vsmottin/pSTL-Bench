#ifndef PSTL_BENCH_PARTITION_GNU_H
#define PSTL_BENCH_PARTITION_GNU_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/algorithm>

namespace benchmark_partition
{
	const auto partition_gnu = [](auto && policy, auto & container, auto & condition) {
		return __gnu_parallel::partition(container.begin(), container.end(), condition);
	};
} // namespace benchmark_partition

#endif //PSTL_BENCH_PARTITION_GNU_H
