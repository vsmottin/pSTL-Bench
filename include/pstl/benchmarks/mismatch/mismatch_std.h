#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_mismatch
{
	const auto mismatch_std = [](auto && policy, const auto & data1, const auto & data2) {
		return std::mismatch(data1.begin(), data1.end(), data2.begin());
	};
} // namespace benchmark_mismatch


