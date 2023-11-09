#ifndef PSTL_BENCH_MERGE_GNU_H
#define PSTL_BENCH_MERGE_GNU_H

#include <parallel/algorithm>

namespace benchmark_merge
{
	const auto merge_gnu = []([[maybe_unused]] auto && policy, auto first1, auto last1, auto first2, auto last2,
	                          auto d_first) {
		return __gnu_parallel::merge(first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_merge

#endif //PSTL_BENCH_MERGE_GNU_H
