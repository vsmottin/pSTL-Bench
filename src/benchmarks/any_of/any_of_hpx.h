
#ifndef PSTL_BENCH_ANY_OF_HPX_H
#define PSTL_BENCH_ANY_OF_HPX_H

#include "pstl/utils.h"
#include <vector>

#include <hpx/algorithm.hpp>

namespace benchmark_any_of
{

	const auto any_of_hpx = [](auto && policy, const auto & container, auto && condition) {
		return hpx::any_of(policy, container.begin(), container.end(), condition);
	};

}

#endif //PSTL_BENCH_ANY_OF_HPX_H
