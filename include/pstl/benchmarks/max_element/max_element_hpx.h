#ifndef PSTL_BENCH_MAX_ELEMENT_HPX_H
#define PSTL_BENCH_MAX_ELEMENT_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_max_element
{
	const auto max_element_hpx = [](auto && policy, const auto & input) {
		return hpx::max_element(policy, input.begin(), input.end());
	};
}

#endif //PSTL_BENCH_MAX_ELEMENT_HPX_H
