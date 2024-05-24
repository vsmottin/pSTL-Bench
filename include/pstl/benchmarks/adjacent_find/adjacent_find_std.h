#pragma once

#include <execution>
#include <numeric>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_std = [](auto && policy, const auto & input) {
		return std::adjacent_find(policy, input.begin(), input.end());
	};
} // namespace benchmark_adjacent_find


