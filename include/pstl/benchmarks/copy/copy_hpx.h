#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy
{
	const auto copy_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::copy(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_copy


