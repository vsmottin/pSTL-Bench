#ifndef PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_STD_H
#define PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_STD_H

#include <cmath>

#include <algorithm>
#include <vector>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_transform_exclusive_scan
{

	const auto transform_exclusive_scan_std = [](auto && policy, auto & input_data, auto & output, auto && f) {
		return std::transform_exclusive_scan(policy, input_data.begin(), input_data.end(), output.begin(),
		                                     pstl::elem_t{}, std::plus<>(), f);
	};

} // namespace benchmark_transform_exclusive_scan

#endif //PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_STD_H
