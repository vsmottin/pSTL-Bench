#ifndef PSTL_BENCH_EXCLUSIVE_SCAN_STD_H
#define PSTL_BENCH_EXCLUSIVE_SCAN_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_exclusive_scan
{
	const auto exclusive_scan_std = [](auto && policy, const auto & container, auto & output) {
		std::exclusive_scan(policy, container.begin(), container.end(), output.begin(), 0);
	};
} // namespace benchmark_exclusive_scan

#endif //PSTL_BENCH_EXCLUSIVE_SCAN_STD_H
