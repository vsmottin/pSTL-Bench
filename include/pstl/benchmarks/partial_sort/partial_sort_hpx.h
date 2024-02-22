#ifndef PSTL_BENCH_PARTIAL_SORT_HPX_H
#define PSTL_BENCH_PARTIAL_SORT_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_partial_sort
{
	const auto partial_sort_hpx = [](auto && policy, auto begin, auto middle, auto end) {
		return hpx::partial_sort(policy, begin, middle, end);
	};
} // namespace benchmark_partial_sort

#endif //PSTL_BENCH_PARTIAL_SORT_HPX_H
