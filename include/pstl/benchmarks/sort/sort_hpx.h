#ifndef PSTL_BENCH_SORT_HPX_H
#define PSTL_BENCH_SORT_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_sort
{
	const auto sort_hpx = [](auto && executionPolicy, auto & input_data) {
		hpx::sort(executionPolicy, input_data.begin(), input_data.end());
	};
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_HPX_H
