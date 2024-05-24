#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_max_element
{
	const auto max_element_std = [](auto && policy, const auto & input) {
		return std::max_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_max_element


