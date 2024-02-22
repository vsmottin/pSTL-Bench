#ifndef PSTL_BENCH_COPY_HPX_H
#define PSTL_BENCH_COPY_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_copy
{
	const auto copy_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::copy(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_copy

#endif //PSTL_BENCH_COPY_HPX_H
