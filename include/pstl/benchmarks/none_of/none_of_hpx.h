
#ifndef PSTL_BENCH_NONE_OF_HPX_H
#define PSTL_BENCH_NONE_OF_HPX_H

#include "pstl/utils.h"
#include <vector>

#include <hpx/algorithm.hpp>

namespace benchmark_none_of
{

	const auto none_of_hpx = [](auto && policy, const auto & container, auto && condition) {
		return hpx::none_of(policy, container.begin(), container.end(), condition);
	};

}

#endif //PSTL_BENCH_NONE_OF_HPX_H
