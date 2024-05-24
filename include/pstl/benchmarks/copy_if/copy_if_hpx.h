#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy_if
{
	const auto copy_if_hpx = [](auto && policy, const auto & container, auto & output, auto && condition) {
		hpx::copy_if(policy, container.begin(), container.end(), output.begin(), condition);
	};
} // namespace benchmark_copy_if


