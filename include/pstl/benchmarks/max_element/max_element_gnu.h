#pragma once

#include <parallel/algorithm>

namespace benchmark_max_element
{
	const auto max_element_gnu = [](auto && policy, const auto & input) {
		return __gnu_parallel::max_element(input.begin(), input.end());
	};
} // namespace benchmark_max_element
