#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_std = [](auto && policy, const auto & container) {
		return std::adjacent_find(policy, container.begin(), container.end());
	};
} // namespace benchmark_adjacent_find


