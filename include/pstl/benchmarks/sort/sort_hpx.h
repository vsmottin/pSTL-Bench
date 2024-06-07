#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_sort
{
	const auto sort_hpx = [](auto && policy, auto & input) {
		hpx::sort(policy, input.begin(), input.end());
	};
} // namespace benchmark_sort
