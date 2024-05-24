#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_copy
{
	const auto copy_std = [](auto && policy, const auto & container, auto & output) {
		std::copy(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_copy


