
#ifndef PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H
#define PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H

#include <vector>
#include <algorithm>
#include <benchmark_utils.h>

namespace B9 {

	const auto b9_1_transform_baseline = [] (auto && policy, const auto & input_data, auto & res, auto && f) {
		std::transform(policy, input_data.begin(), input_data.end(), res.begin(), f);
	};

}

#endif //PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H
