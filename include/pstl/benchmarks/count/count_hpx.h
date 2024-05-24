#pragma once

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_count
{
	const auto count_hpx = [](auto && policy, const auto & input, const auto & value) {
		return hpx::count(policy, input.begin(), input.end(), value);
	};
} // namespace benchmark_count


