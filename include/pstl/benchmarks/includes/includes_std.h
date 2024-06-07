#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_includes
{
	const auto includes_std = [](auto && policy, const auto & input, const auto & subset) {
		return std::includes(policy, input.begin(), input.end(), subset.begin(), subset.end());
	};
} // namespace benchmark_includes
