
#ifndef PSTL_BENCH_B6_1_INCLUSIVE_SCAN_OMP_H
#define PSTL_BENCH_B6_1_INCLUSIVE_SCAN_OMP_H

#include <benchmark_utils.h>
#include <numeric>
#include <utility>
#include <vector>

#include <omp_helpers.h>

namespace B6
{

	const auto b6_1_inclusive_scan_omp = [](auto && policy, const auto & container, auto & result) {
		omp::inclusive_scan(policy, container.begin(), container.end(), result.begin());
	};

}

#endif //PSTL_BENCH_B6_1_INCLUSIVE_SCAN_OMP_H
