#ifndef PSTL_BENCH_SORT_OMP_H
#define PSTL_BENCH_SORT_OMP_H

#include <omp_helpers.h>

namespace benchmark_sort
{
	const auto sort_omp = [](auto && executionPolicy, auto & input_data) {
		omp::sort(executionPolicy, input_data.begin(), input_data.end());
	};
}

#endif //PSTL_BENCH_SORT_OMP_H
