#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_is_sorted
{
	const auto is_sorted_hpx = [](auto && policy, const auto & input) {
		return hpx::is_sorted(policy, input.begin(), input.end());
	};
} // namespace benchmark_is_sorted
