#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_STD_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_std = [](auto && policy, const auto & container, auto & output) {
		std::adjacent_difference(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_STD_H
