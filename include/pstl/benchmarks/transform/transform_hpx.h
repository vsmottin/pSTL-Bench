#ifndef PSTL_BENCH_TRANSFORM_HPX_H
#define PSTL_BENCH_TRANSFORM_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_transform
{

	const auto transform_hpx = [](auto && policy, auto & input_data, auto && f) {
		hpx::transform(policy, input_data.begin(), input_data.end(), input_data.begin(), f);
	};

}

#endif //PSTL_BENCH_TRANSFORM_HPX_H
