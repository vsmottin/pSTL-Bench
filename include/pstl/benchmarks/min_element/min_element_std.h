#pragma once

#include <execution>
#include <numeric>

namespace benchmark_min_element
{
	const auto min_element_std = [](auto && policy, const auto & input) {
		return std::min_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_min_element
