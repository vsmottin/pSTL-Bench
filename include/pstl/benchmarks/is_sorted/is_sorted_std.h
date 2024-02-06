#ifndef PSTL_BENCH_IS_SORTED_STD_H
#define PSTL_BENCH_IS_SORTED_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_is_sorted
{
	const auto is_sorted_std = [](auto && policy, const auto & input) {
		return std::is_sorted(policy, input.begin(), input.end());
	};
} // namespace benchmark_is_sorted

#endif //PSTL_BENCH_IS_SORTED_STD_H
