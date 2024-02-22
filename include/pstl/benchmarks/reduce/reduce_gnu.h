#ifndef PSTL_BENCH_REDUCE_GNU_H
#define PSTL_BENCH_REDUCE_GNU_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

#include <parallel/numeric>

namespace benchmark_reduce
{
	const auto reduce_gnu = [](auto && policy, const auto & container) {
		return __gnu_parallel::accumulate(container.begin(), container.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce

#endif //PSTL_BENCH_REDUCE_GNU_H
