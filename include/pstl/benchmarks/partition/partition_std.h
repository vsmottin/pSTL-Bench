#pragma once

#include <algorithm>

namespace benchmark_partition
{
	const auto partition_std = [](auto && policy, auto & input, auto && condition) {
		return std::partition(policy, input.begin(), input.end(), std::forward<decltype(condition)>(condition));
	};
} // namespace benchmark_partition
