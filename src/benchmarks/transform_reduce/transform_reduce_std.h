#ifndef PSTL_BENCH_TRANSFORM_REDUCE_STD_H
#define PSTL_BENCH_TRANSFORM_REDUCE_STD_H


#include <algorithm>
#include <benchmark/benchmark.h>
#include <benchmark_utils.h>
#include <cmath>
#include <vector>

namespace benchmark_transform_reduce
{

	const auto transform_reduce_std = [](auto && policy, auto & input_data, auto && f) {
		return std::transform_reduce(policy, input_data.begin(), input_data.end(), 0, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_STD_H
