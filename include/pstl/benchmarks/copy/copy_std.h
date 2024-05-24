#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_copy
{
	const auto copy_std = [](auto && policy, const auto & input, auto & output) {
		std::copy(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_copy


