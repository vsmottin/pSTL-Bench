#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_partition
{
	const auto partition_hpx = [](auto && policy, auto && begin, auto && end, auto && condition) {
		return hpx::partition(policy, begin, end, condition);
	};
} // namespace benchmark_partition


