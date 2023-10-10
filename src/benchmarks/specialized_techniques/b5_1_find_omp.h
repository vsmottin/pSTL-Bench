
#ifndef PSTL_BENCH_B5_1_FIND_OMP_H
#define PSTL_BENCH_B5_1_FIND_OMP_H

#include <algorithm>
#include <vector>

#include <omp_helpers.h>

#include <benchmark_utils.h>

namespace B5
{

	const auto b5_1_find_omp = [](auto && policy, const auto & container, const auto & find_val) {
		return omp::find(policy, container.begin(), container.end(), find_val);
	};

}

#endif //PSTL_BENCH_B5_1_FIND_OMP_H
