#pragma once

#include <hpx/numeric.hpp>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_hpx = [](auto & policy, const auto & input, auto & output) {
		hpx::adjacent_difference(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference
