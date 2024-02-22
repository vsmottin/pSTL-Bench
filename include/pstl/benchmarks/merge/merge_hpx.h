#ifndef PSTL_BENCH_MERGE_HPX_H
#define PSTL_BENCH_MERGE_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_merge
{
	const auto merge_hpx = [](auto && policy, auto first1, auto last1, auto first2, auto last2, auto d_first) {
		return hpx::merge(policy, first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_merge

#endif //PSTL_BENCH_MERGE_HPX_H
