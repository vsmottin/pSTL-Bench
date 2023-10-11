#ifndef PSTL_BENCH_SORT_STD_H
#define PSTL_BENCH_SORT_STD_H

#include <algorithm>
#include <execution>

namespace benchmark_sort
{
	const auto sort_std = [](auto && executionPolicy, auto & input_data) {
		std::sort(executionPolicy, input_data.begin(), input_data.end());
	};
}

#endif //PSTL_BENCH_SORT_STD_H
