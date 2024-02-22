#ifndef PSTL_BENCH_INPLACE_MERGE_HPX_H
#define PSTL_BENCH_INPLACE_MERGE_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_inplace_merge
{
	const auto inplace_merge_hpx = [](auto && policy, auto begin, auto middle, auto end) {
		return hpx::inplace_merge(policy, begin, middle, end);
	};
} // namespace benchmark_inplace_merge

#endif //PSTL_BENCH_INPLACE_MERGE_HPX_H
