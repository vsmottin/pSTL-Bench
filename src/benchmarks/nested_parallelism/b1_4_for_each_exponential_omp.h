#ifndef PSTL_BENCH_B1_4_FOR_EACH_EXPONENTIAL_OMP_H
#define PSTL_BENCH_B1_4_FOR_EACH_EXPONENTIAL_OMP_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <iostream>

#include <omp.h>

#include <omp_helpers.h>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace B1 {

	template<class ExecutionPolicy>
	struct FIB_omp {

		typedef suite::base_type<ExecutionPolicy> BASE_POLICY;

		ExecutionPolicy m_policy;

		explicit FIB_omp (ExecutionPolicy & policy) : m_policy(policy) {}

		void operator() (const int & index) {
			if (index <= 0) {
				return;
			}

			double value = std::tan(index) + std::cos(index);
			benchmark::DoNotOptimize(value);


			auto next = suite::get_vec<BASE_POLICY>(2);
			next = {index - 1, index - 2};

			omp::for_each(m_policy, next.begin(), next.end(), FIB_omp{m_policy});
		}
	};

	const auto b1_4_for_each_exponential_omp = [] (auto && policy, const auto & input_data) {
		// enable nested parallelism
		omp_set_nested(1);

		omp::for_each(policy, input_data.begin(), input_data.end(), FIB_omp{policy});

	};

}

#endif //PSTL_BENCH_B1_4_FOR_EACH_EXPONENTIAL_OMP_H
