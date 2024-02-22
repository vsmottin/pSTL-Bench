
#ifndef PSTL_BENCH_FOR_EACH_GNU_H
#define PSTL_BENCH_FOR_EACH_GNU_H

#include <vector>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

#include <parallel/algorithm>

namespace benchmark_for_each
{

	const auto for_each_gnu = [](auto && policy, const auto & input_data, auto && f) {
		__gnu_parallel::for_each(input_data.begin(), input_data.end(), f);
	};

} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_GNU_H
