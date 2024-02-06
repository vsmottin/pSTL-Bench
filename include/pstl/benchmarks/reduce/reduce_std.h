#ifndef PSTL_BENCH_REDUCE_STD_H
#define PSTL_BENCH_REDUCE_STD_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_reduce
{
	const auto reduce_std = [](auto && policy, const auto & container) {
		return std::reduce(policy, container.begin(), container.end(), 0);
	};
}

#endif //PSTL_BENCH_REDUCE_STD_H
