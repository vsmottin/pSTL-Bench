#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_is_sorted
{
	const auto is_sorted_std = [](auto && policy, const auto & begin, const auto & end) -> bool {
		return std::is_sorted(policy, begin, end);
	};
} // namespace benchmark_is_sorted


