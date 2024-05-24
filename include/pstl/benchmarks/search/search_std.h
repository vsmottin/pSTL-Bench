#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_search
{
	const auto search_std = [](auto && policy, const auto & data1, const auto & data2) {
		return std::search(policy, data1.begin(), data1.end(), data2.begin(), data2.end());
	};
} // namespace benchmark_search
