#ifndef PSTL_BENCH_TRANSFORM_REDUCE_HPX_H
#define PSTL_BENCH_TRANSFORM_REDUCE_HPX_H

#include <functional>

#include <hpx/algorithm.hpp>

namespace benchmark_transform_reduce
{

	const auto transform_reduce_hpx = [](auto && policy, auto & input_data, auto && f) {
		// Get the type of the input data
		using T = std::iterator_traits<decltype(input_data.cbegin())>::value_type;

		return hpx::transform_reduce(policy, input_data.begin(), input_data.end(), T{}, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_HPX_H
