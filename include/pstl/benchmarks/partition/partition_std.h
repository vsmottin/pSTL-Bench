#ifndef PSTL_BENCH_PARTITION_STD_H
#define PSTL_BENCH_PARTITION_STD_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_partition
{
	const auto partition_std = [](auto && policy, auto & container, auto & condition) {
		return std::partition(policy, container.begin(), container.end(), condition);
	};
}

#endif //PSTL_BENCH_PARTITION_STD_H
