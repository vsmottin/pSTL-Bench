#ifndef PSTL_BENCH_FILL_STD_H
#define PSTL_BENCH_FILL_STD_H

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_fill
{
	const auto fill_std = [](auto && policy, auto & container, const auto & value) {
		return std::fill(policy, container.begin(), container.end(), value);
	};
}

#endif //PSTL_BENCH_FILL_STD_H
