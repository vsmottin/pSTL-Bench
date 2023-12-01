#ifndef PSTL_BENCH_TRANSFORM_REDUCE_HPX_H
#define PSTL_BENCH_TRANSFORM_REDUCE_HPX_H

#include <functional>

#include <hpx/algorithm.hpp>

namespace benchmark_transform_reduce
{

	const auto transform_reduce_hpx = [](auto && policy, auto & input_data, auto && f) {
		return hpx::transform_reduce(policy, input_data.begin(), input_data.end(), 0, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_HPX_H
