#ifndef PSTL_BENCH_SORT_STD_H
#define PSTL_BENCH_SORT_STD_H

#include <algorithm>
#include <execution>

#ifdef USE_TBB
#include <tbb/parallel_sort.h>
#endif //USE_TBB

namespace benchmark_sort
{
	const auto sort_std = [](auto && executionPolicy, auto & input_data) {
#ifdef USE_TBB
		// Show compiler message if TBB is used
#warning "Using TBB parallel_sort"
		tbb::parallel_sort(input_data.begin(), input_data.end());
#else
		std::sort(executionPolicy, input_data.begin(), input_data.end());
#endif //USE_TBB
	};
}

#endif //PSTL_BENCH_SORT_STD_H
