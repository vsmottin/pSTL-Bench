#ifndef PSTL_BENCH_COPY_IF_HPX_H
#define PSTL_BENCH_COPY_IF_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_copy_if
{
	const auto copy_if_hpx = [](auto && policy, const auto & container, auto & output, auto && condition) {
		hpx::copy_if(policy, container.begin(), container.end(), output.begin(), condition);
	};
} // namespace benchmark_copy_if

#endif //PSTL_BENCH_COPY_IF_HPX_H
