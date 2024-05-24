#pragma once

#include <parallel/algorithm>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_gnu = []([[maybe_unused]] auto && policy, const auto & input) {
		return __gnu_parallel::adjacent_find(input.begin(), input.end());
	};
} // namespace benchmark_adjacent_find
