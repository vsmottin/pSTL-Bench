
#ifndef PSTL_BENCH_FIND_HPX_H
#define PSTL_BENCH_FIND_HPX_H

#include <vector>

#include <hpx/algorithm.hpp>

namespace benchmark_find
{
	const auto find_hpx = [](auto && policy, const auto & container, const auto & find_val) {
		return hpx::find(policy, container.begin(), container.end(), find_val);
	};
} // namespace benchmark_find

#endif //PSTL_BENCH_FIND_HPX_H
