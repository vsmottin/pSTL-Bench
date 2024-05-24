#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_exclusive_scan
{
	const auto exclusive_scan_std = [](auto && policy, const auto & input, auto & output) {
		std::exclusive_scan(policy, input.begin(), input.end(), output.begin(), 0);
	};
} // namespace benchmark_exclusive_scan
