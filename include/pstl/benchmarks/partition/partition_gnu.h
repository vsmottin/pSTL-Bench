#pragma once

#include <parallel/algorithm>

namespace benchmark_partition
{
	const auto partition_gnu = []([[maybe_unused]] auto && policy, auto & input, auto && condition) {
		return __gnu_parallel::partition(input.begin(), input.end(), std::forward<decltype(condition)>(condition));
	};
} // namespace benchmark_partition
