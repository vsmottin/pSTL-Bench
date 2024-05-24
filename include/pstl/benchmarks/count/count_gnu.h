#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/algorithm>

namespace benchmark_count
{
	const auto count_gnu = [](auto && policy, const auto & container, const auto & value) {
		return __gnu_parallel::count(container.begin(), container.end(), value);
	};
} // namespace benchmark_count


