#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_sort
{
	const auto sort_hpx = [](auto && policy, auto && begin, auto && end) {
		hpx::sort(policy, begin, end);
	};
} // namespace benchmark_sort


