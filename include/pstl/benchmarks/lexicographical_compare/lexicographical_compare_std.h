#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_lexicographical_compare
{
	const auto lexicographical_compare_std = [](auto && policy, const auto & data_a, const auto & data_b) {
		return std::lexicographical_compare(policy, data_a.begin(), data_a.end(), data_b.begin(), data_b.end());
	};
} // namespace benchmark_lexicographical_compare
