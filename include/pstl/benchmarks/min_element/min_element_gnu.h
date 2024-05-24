#pragma once

#include <parallel/algorithm>

namespace benchmark_min_element
{
	const auto min_element_gnu = [](auto && policy, const auto & input) {
		return __gnu_parallel::min_element(input.begin(), input.end());
	};
} // namespace benchmark_min_element


