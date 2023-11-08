#ifndef PSTL_BENCH_ALL_OF_HPX_H
#define PSTL_BENCH_ALL_OF_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_all_of
{
	const auto all_of_hpx = [](auto && policy, const auto & container, auto && condition) {
		return hpx::all_of(policy, container.begin(), container.end(), condition);
	};
}

#endif //PSTL_BENCH_ALL_OF_HPX_H
