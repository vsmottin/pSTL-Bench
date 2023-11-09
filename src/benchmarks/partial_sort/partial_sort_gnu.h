#ifndef PSTL_BENCH_PARTIAL_SORT_GNU_H
#define PSTL_BENCH_PARTIAL_SORT_GNU_H

#include <parallel/algorithm>

namespace benchmark_partial_sort
{
	const auto partial_sort_gnu = []([[maybe_unused]] auto && policy, auto begin, auto middle, auto end) {
		return __gnu_parallel::partial_sort(begin, middle, end);
	};
} // namespace benchmark_partial_sort

#endif //PSTL_BENCH_PARTIAL_SORT_GNU_H
