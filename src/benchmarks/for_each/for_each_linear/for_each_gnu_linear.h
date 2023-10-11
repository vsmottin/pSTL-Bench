
#ifndef PSTL_BENCH_FOR_EACH_GNU_LINEAR_H
#define PSTL_BENCH_FOR_EACH_GNU_LINEAR_H

#include <vector>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu_linear = [](auto && policy, const auto & input_data, auto && f) {
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), f);
	};

}

#endif //PSTL_BENCH_FOR_EACH_GNU_LINEAR_H
