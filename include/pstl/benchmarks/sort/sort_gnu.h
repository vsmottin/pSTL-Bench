#ifndef PSTL_BENCH_SORT_GNU_H
#define PSTL_BENCH_SORT_GNU_H

#include <parallel/parallel.h>

namespace benchmark_sort
{
	const auto sort_gnu = []([[maybe_unused]] auto && executionPolicy, auto & input_data) {
		__gnu_parallel::sort(input_data.begin(), input_data.end());
	};
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_GNU_H
