#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_HPX_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_HPX_H

#include <hpx/numeric.hpp>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::adjacent_difference(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_HPX_H
