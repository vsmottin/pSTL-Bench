#pragma once

#include <execution>
#include <numeric>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_std = [](auto & policy, const auto & input, auto & output) {
		std::adjacent_difference(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference
