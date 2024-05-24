#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_inclusive_scan
{
	const auto inclusive_scan_std = [](auto && policy, const auto & input, auto & output) {
		std::inclusive_scan(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_inclusive_scan
