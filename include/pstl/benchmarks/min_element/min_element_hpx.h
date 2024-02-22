#ifndef PSTL_BENCH_MIN_ELEMENT_HPX_H
#define PSTL_BENCH_MIN_ELEMENT_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_min_element
{
	const auto min_element_hpx = [](auto && policy, const auto & input) {
		return hpx::min_element(policy, input.begin(), input.end());
	};
} // namespace benchmark_min_element

#endif //PSTL_BENCH_MIN_ELEMENT_HPX_H
