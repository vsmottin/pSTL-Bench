#pragma once

#include <algorithm>

namespace benchmark_partition
{
	const auto partition_std = [](auto && policy, auto && begin, auto && end, auto && condition) {
		return std::partition(policy, begin, end, condition);
	};
} // namespace benchmark_partition


