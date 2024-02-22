#ifndef PSTL_BENCH_SEARCH_GNU_H
#define PSTL_BENCH_SEARCH_GNU_H

#include <parallel/algorithm>

namespace benchmark_search
{
	const auto search_gnu = []([[maybe_unused]] auto && policy, const auto & first1, const auto & last1,
	                           const auto & first2, const auto & last2) {
		return __gnu_parallel::search(first1, last1, first2, last2);
	};
} // namespace benchmark_search

#endif //PSTL_BENCH_SEARCH_GNU_H
