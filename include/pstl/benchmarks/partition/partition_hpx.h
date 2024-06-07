#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_partition
{
	const auto partition_hpx = [](auto && policy, auto & input, auto && condition) {
		return hpx::partition(policy, input.begin(), input.end(), std::forward<decltype(condition)>(condition));
	};
} // namespace benchmark_partition
