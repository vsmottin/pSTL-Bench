#ifndef PSTL_BENCH_PARTITION_HPX_H
#define PSTL_BENCH_PARTITION_HPX_H

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_partition
{
	const auto partition_hpx = [](auto && policy, auto & container, auto & condition) {
		return hpx::partition(policy, container.begin(), container.end(), condition);
	};
} // namespace benchmark_partition

#endif //PSTL_BENCH_PARTITION_HPX_H
