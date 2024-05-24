#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/algorithm>

namespace benchmark_count_if
{
	const auto count_if_gnu = [](auto && policy, const auto & input, auto & condition) {
		return __gnu_parallel::count_if(input.begin(), input.end(), condition);
	};
} // namespace benchmark_count_if
