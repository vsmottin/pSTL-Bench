
#ifndef PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_OMP_H
#define PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_OMP_H

#include <numeric>
#include <utility>
#include <vector>

#include <benchmark_utils.h>

#include <omp_helpers.h>

namespace B6
{

	const auto b6_2_exclusive_scan_omp = [](auto && policy, const auto & container, auto & result) {
		omp::exclusive_scan(policy, container.begin(), container.end(), result.begin(), 0);
	};

}

#endif //PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_OMP_H
