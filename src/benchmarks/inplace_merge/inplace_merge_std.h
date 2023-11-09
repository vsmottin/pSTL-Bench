#ifndef PSTL_BENCH_INPLACE_MERGE_STD_H
#define PSTL_BENCH_INPLACE_MERGE_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_inplace_merge
{
	const auto inplace_merge_std = [](auto && policy, auto begin, auto middle, auto end) {
		return std::inplace_merge(policy, begin, middle, end);
	};
} // namespace benchmark_inplace_merge

#endif //PSTL_BENCH_INPLACE_MERGE_STD_H
