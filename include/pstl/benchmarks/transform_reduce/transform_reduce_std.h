#ifndef PSTL_BENCH_TRANSFORM_REDUCE_STD_H
#define PSTL_BENCH_TRANSFORM_REDUCE_STD_H

#include <algorithm>
#include <vector>

#include <cmath>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_transform_reduce
{

	const auto transform_reduce_std = [](auto && policy, auto & input_data, auto && f) {
		return std::transform_reduce(policy, input_data.cbegin(), input_data.cend(), pstl::elem_t{}, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_STD_H
