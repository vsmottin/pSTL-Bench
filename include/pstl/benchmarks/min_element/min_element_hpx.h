#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_min_element
{
	const auto min_element_hpx = [](auto && policy, const auto & input) {
		return hpx::min_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_min_element


