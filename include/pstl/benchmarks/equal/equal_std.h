#ifndef PSTL_BENCH_EQUAL_STD_H
#define PSTL_BENCH_EQUAL_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_equal
{
	const auto equal_std = [](auto && policy, const auto & container, auto & output) {
		std::equal(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_equal

#endif //PSTL_BENCH_EQUAL_STD_H
