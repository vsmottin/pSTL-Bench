#ifndef PSTL_BENCH_TRANSFORM_STD_H
#define PSTL_BENCH_TRANSFORM_STD_H


#include <algorithm>
#include <benchmark/benchmark.h>
#include <benchmark_utils.h>
#include <cmath>
#include <vector>

namespace benchmark_transform
{

	const auto transform_std = [](auto && policy, auto & input_data, auto && f) {
		std::transform(policy, input_data.begin(), input_data.end(), input_data.begin(), f);
	};

}

#endif //PSTL_BENCH_TRANSFORM_STD_H
