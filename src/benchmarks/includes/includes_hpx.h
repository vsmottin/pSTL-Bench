#ifndef PSTL_BENCH_INCLUDES_HPX_H
#define PSTL_BENCH_INCLUDES_HPX_H

#include <hpx/numeric.hpp>

namespace benchmark_includes
{
	const auto includes_hpx = [](auto && policy, const auto & container, const auto & subset) {
		return hpx::includes(policy, container.begin(), container.end(), subset.begin(), subset.end());
	};
}

#endif //PSTL_BENCH_INCLUDES_HPX_H
