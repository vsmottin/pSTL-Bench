#ifndef PSTL_BENCH_ADJACENT_FIND_HPX_H
#define PSTL_BENCH_ADJACENT_FIND_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_hpx = [](auto && policy, const auto & container) {
		return hpx::adjacent_find(policy, container.begin(), container.end());
	};
} // namespace benchmark_adjacent_find

#endif //PSTL_BENCH_ADJACENT_FIND_HPX_H
