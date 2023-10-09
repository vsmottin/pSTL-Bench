
#ifndef PSTL_BENCH_B1_1_FOR_EACH_LINEAR_GNU_H
#define PSTL_BENCH_B1_1_FOR_EACH_LINEAR_GNU_H

#include <vector>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

#include <parallel/algorithm>

namespace B1
{

	const auto b1_1_for_each_linear_gnu = [](auto && policy, const auto & input_data, auto && f) {
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), f);
	};

}

#endif //PSTL_BENCH_B1_1_FOR_EACH_LINEAR_GNU_H
