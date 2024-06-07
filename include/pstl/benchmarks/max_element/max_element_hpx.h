#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_max_element
{
	const auto max_element_hpx = [](auto && policy, const auto & input) {
		return hpx::max_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_max_element
