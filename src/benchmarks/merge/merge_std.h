#ifndef PSTL_BENCH_MERGE_STD_H
#define PSTL_BENCH_MERGE_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_merge
{
	const auto merge_std = [](auto && policy, auto first1, auto last1, auto first2, auto last2, auto d_first) {
		return std::merge(policy, first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_merge

#endif //PSTL_BENCH_MERGE_STD_H
