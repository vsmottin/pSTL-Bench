
#ifndef PSTL_BENCH_B9_7_TRANSFORM_OMP_H
#define PSTL_BENCH_B9_7_TRANSFORM_OMP_H

#include <vector>

namespace B9 {

	const auto b9_7_transform_omp = [] (auto && policy, const auto & input_data, auto & res, auto && f) {
		// if policy is std::execution::parallel_unsequenced_policy -> parallelization + vectorization
		if (std::is_same_v<decltype(policy), std::execution::parallel_unsequenced_policy>) {
#pragma omp parallel for simd
			for (std::size_t i = 0; i < input_data.size(); ++i) {
				res[i] = f(input_data[i]);
			}
		}
			// if policy is std::execution::parallel_policy -> parallelization
		else if (std::is_same_v<decltype(policy), std::execution::parallel_policy>) {
#pragma omp parallel for
			for (std::size_t i = 0; i < input_data.size(); ++i) {
				res[i] = f(input_data[i]);
			}
		}
			// if policy is std::execution::unsequenced_policy -> vectorization
		else if (std::is_same_v<decltype(policy), std::execution::unsequenced_policy>) {
#pragma omp simd
			for (std::size_t i = 0; i < input_data.size(); ++i) {
				res[i] = f(input_data[i]);
			}
		}
			// if policy is std::execution::sequenced_policy or any other unknown policy -> forward to the default...
		else {
			std::transform(policy, input_data.begin(), input_data.end(), res.begin(), f);
		}
	};

}

#endif //PSTL_BENCH_B9_7_TRANSFORM_OMP_H
