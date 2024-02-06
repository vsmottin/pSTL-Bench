#ifndef PSTL_BENCH_IS_SORTED_HPX_H
#define PSTL_BENCH_IS_SORTED_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_is_sorted
{
	const auto is_sorted_hpx = [](auto && policy, const auto & input) {
		return hpx::is_sorted(policy, input.begin(), input.end());
	};
}

#endif //PSTL_BENCH_IS_SORTED_HPX_H
