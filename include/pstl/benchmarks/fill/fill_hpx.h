#pragma once

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

namespace benchmark_fill
{
	const auto fill_hpx = [](auto && policy, auto & input, const auto & value) {
		return hpx::fill(policy, input.begin(), input.end(), value);
	};
} // namespace benchmark_fill
