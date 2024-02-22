#ifndef PSTL_BENCH_REDUCE_HPX_H
#define PSTL_BENCH_REDUCE_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_reduce
{
	const auto reduce_hpx = [](auto && policy, const auto & container) {
		return hpx::reduce(policy, container.begin(), container.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce

#endif //PSTL_BENCH_REDUCE_HPX_H
