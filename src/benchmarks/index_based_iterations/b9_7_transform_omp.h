
#ifndef PSTL_BENCH_B9_7_TRANSFORM_OMP_H
#define PSTL_BENCH_B9_7_TRANSFORM_OMP_H

#include <vector>

#include <omp_helpers.h>

namespace B9 {

	const auto b9_7_transform_omp = [] (auto && policy, const auto & input_data, auto & res, auto && f) {
		omp::transform(policy, std::begin(input_data), std::end(input_data), std::begin(res), f);
	};

}

#endif //PSTL_BENCH_B9_7_TRANSFORM_OMP_H
