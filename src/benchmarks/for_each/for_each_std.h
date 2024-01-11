#ifndef PSTL_BENCH_FOR_EACH_STD_H
#define PSTL_BENCH_FOR_EACH_STD_H


#include "pstl/utils.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <vector>

namespace benchmark_for_each
{

	const auto for_each_std = [](auto && policy, const auto & input_data, auto && f) {
		std::for_each(policy, input_data.begin(), input_data.end(), f);
	};

}

#endif //PSTL_BENCH_FOR_EACH_STD_H
