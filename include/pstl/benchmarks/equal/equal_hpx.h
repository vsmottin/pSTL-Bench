#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_equal
{
	const auto equal_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::equal(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_equal


