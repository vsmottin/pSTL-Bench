#pragma once

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_count_if
{
	const auto count_if_hpx = [](auto && policy, const auto & input, auto & condition) {
		return hpx::count_if(policy, input.begin(), input.end(), condition);
	};
} // namespace benchmark_count_if


