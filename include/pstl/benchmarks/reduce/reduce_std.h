#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_reduce
{
	const auto reduce_std = [](auto && policy, const auto & begin, const auto & end) {
		return std::reduce(policy, begin, end, pstl::elem_t{});
	};
} // namespace benchmark_reduce


