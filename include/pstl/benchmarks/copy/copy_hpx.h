#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy
{
	const auto copy_hpx = [](auto && policy, const auto & input, auto & output) {
		hpx::copy(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_copy


