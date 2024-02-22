
#ifndef PSTL_BENCH_TRANSFORM_GNU_H
#define PSTL_BENCH_TRANSFORM_GNU_H

#include <vector>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

#include <parallel/algorithm>

namespace benchmark_transform
{

	const auto transform_gnu = [](auto && policy, auto & input_data, auto && f) {
		__gnu_parallel::transform(input_data.begin(), input_data.end(), input_data.begin(), f);
	};

} // namespace benchmark_transform

#endif //PSTL_BENCH_TRANSFORM_GNU_H
