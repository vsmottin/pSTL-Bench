#ifndef MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H
#define MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H


#include <algorithm>
#include <benchmark/benchmark.h>
#include <benchmark_utils.h>
#include <cmath>
#include <vector>

namespace B1
{

	const auto b1_1_for_each_linear = [](auto && policy, const auto & input_data, auto && f) {
		std::for_each(policy, input_data.begin(), input_data.end(), f);
	};

}

#endif //MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H
