#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_fill
{
	const auto fill_std = [](auto && policy, auto & container, const auto & value) {
		return std::fill(policy, container.begin(), container.end(), value);
	};
} // namespace benchmark_fill


