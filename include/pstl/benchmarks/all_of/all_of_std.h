#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_all_of
{
	const auto all_of_std = [](auto && policy, const auto & container, auto && condition) {
		return std::all_of(policy, container.begin(), container.end(), condition);
	};
} // namespace benchmark_all_of


