#ifndef PSTL_BENCH_COUNT_STD_H
#define PSTL_BENCH_COUNT_STD_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_count
{
	const auto count_std = [](auto && policy, const auto & container, const auto & value) {
		return std::count(policy, container.begin(), container.end(), value);
	};
}

#endif //PSTL_BENCH_COUNT_STD_H
