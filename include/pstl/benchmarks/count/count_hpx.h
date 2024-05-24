#pragma once

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_count
{
	const auto count_hpx = [](auto && policy, const auto & container, const auto & value) {
		return hpx::count(policy, container.begin(), container.end(), value);
	};
} // namespace benchmark_count


