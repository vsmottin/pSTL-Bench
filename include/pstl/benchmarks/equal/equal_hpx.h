#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_equal
{
	const auto equal_hpx = [](auto && policy, const auto & input, auto & output) {
		hpx::equal(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_equal
