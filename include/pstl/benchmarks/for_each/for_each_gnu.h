
#pragma once

#include <vector>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu = [](auto && policy, auto & input_data, auto && f) {
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), f);
	};

} // namespace benchmark_for_each


