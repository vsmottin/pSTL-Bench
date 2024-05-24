#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_includes
{
	const auto includes_std = [](auto && policy, const auto & container, const auto & subset) {
		return std::includes(policy, container.begin(), container.end(), subset.begin(), subset.end());
	};
} // namespace benchmark_includes


