#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/numeric>

namespace benchmark_reduce
{
	const auto reduce_gnu = []([[maybe_unused]] auto && policy, const auto & begin, const auto & end) {
		return __gnu_parallel::accumulate(begin, end, pstl::elem_t{});
	};
} // namespace benchmark_reduce


