#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_copy_if
{
	const auto copy_if_std = [](auto && policy, const auto & input, auto & output, auto && condition) {
		std::copy_if(policy, input.begin(), input.end(), output.begin(), condition);
	};
} // namespace benchmark_copy_if
