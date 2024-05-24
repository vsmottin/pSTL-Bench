#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_hpx = [](auto && policy, const auto & input) {
		return hpx::adjacent_find(policy, input.begin(), input.end());
	};
} // namespace benchmark_adjacent_find
