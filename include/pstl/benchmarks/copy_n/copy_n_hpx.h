#ifndef PSTL_BENCH_COPY_N_HPX_H
#define PSTL_BENCH_COPY_N_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_copy_n
{
	const auto copy_n_hpx = [](auto && policy, const auto & container, const auto & n, auto & output) {
		hpx::copy_n(policy, container.begin(), n, output.begin());
	};
} // namespace benchmark_copy_n

#endif //PSTL_BENCH_COPY_N_HPX_H
