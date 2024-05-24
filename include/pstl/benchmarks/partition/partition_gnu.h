#pragma once

#include <parallel/algorithm>

namespace benchmark_partition
{
	const auto partition_gnu = []([[maybe_unused]] auto && policy, auto && begin, auto && end, auto && condition) {
		return __gnu_parallel::partition(begin, end, condition);
	};
} // namespace benchmark_partition


