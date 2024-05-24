#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy_if
{
	const auto copy_if_hpx = [](auto && policy, const auto & input, auto & output, auto && condition) {
		hpx::copy_if(policy, input.begin(), input.end(), output.begin(), condition);
	};
} // namespace benchmark_copy_if


