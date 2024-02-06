#ifndef PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_STD_H
#define PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_STD_H


#include "pstl/utils.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

namespace benchmark_transform_inclusive_scan
{

	const auto transform_inclusive_scan_std = [](auto && policy, auto & input_data, auto & output, auto && f) {
		return std::transform_inclusive_scan(policy, input_data.begin(), input_data.end(), output.begin(),
		                                     std::plus<>(), f);
	};

}

#endif //PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_STD_H
