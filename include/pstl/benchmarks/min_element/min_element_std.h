#ifndef PSTL_BENCH_MIN_ELEMENT_STD_H
#define PSTL_BENCH_MIN_ELEMENT_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_min_element
{
	const auto min_element_std = [](auto && policy, const auto & input) {
		return std::min_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_min_element

#endif //PSTL_BENCH_MIN_ELEMENT_STD_H
