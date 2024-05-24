#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_is_sorted
{
	const auto is_sorted_std = [](auto && policy, const auto & input) -> bool {
		return std::is_sorted(policy, input.begin(), input.end());
	};
} // namespace benchmark_is_sorted
