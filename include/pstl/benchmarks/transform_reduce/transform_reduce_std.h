#ifndef PSTL_BENCH_TRANSFORM_REDUCE_STD_H
#define PSTL_BENCH_TRANSFORM_REDUCE_STD_H


#include "pstl/utils.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

namespace benchmark_transform_reduce
{

	const auto transform_reduce_std = [](auto && policy, auto & input_data, auto && f) {
		// Get the type of the input data
		using T = std::iterator_traits<decltype(input_data.cbegin())>::value_type;

		return std::transform_reduce(policy, input_data.cbegin(), input_data.cend(), T{}, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_STD_H
