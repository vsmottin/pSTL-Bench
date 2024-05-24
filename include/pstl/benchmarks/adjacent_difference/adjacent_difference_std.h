#pragma once

#include <numeric>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_std = [](auto & policy, const auto & container, auto & output) {
		std::adjacent_difference(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference
