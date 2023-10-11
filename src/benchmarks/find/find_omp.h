
#ifndef PSTL_BENCH_FIND_OMP_H
#define PSTL_BENCH_FIND_OMP_H

#include <algorithm>
#include <vector>

#include <omp_helpers.h>

#include <benchmark_utils.h>

namespace benchmark_find
{

	const auto find_omp = [](auto && policy, const auto & container, const auto & find_val) {
		return omp::find(policy, container.begin(), container.end(), find_val);
	};

}

#endif //PSTL_BENCH_FIND_OMP_H
