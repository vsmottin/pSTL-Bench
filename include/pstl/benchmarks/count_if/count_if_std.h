#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_count_if
{
	const auto count_if_std = [](auto && policy, const auto & container, auto & condition) {
		return std::count_if(policy, container.begin(), container.end(), condition);
	};
} // namespace benchmark_count_if


