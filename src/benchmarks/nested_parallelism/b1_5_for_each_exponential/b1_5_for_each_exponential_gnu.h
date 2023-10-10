#ifndef PSTL_BENCH_B1_5_FOR_EACH_EXPONENTIAL_GNU_H
#define PSTL_BENCH_B1_5_FOR_EACH_EXPONENTIAL_GNU_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>

#include <parallel/algorithm>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace B1
{

	template<class ExecutionPolicy>
	struct FIB_gnu
	{
		typedef suite::base_type<ExecutionPolicy> BASE_POLICY;

		ExecutionPolicy m_policy;

		explicit FIB_gnu(ExecutionPolicy & policy) : m_policy(policy) {}

		void operator()(const int & index)
		{
			if (index <= 0) { return; }

			double value = std::tan(index) + std::cos(index);
			benchmark::DoNotOptimize(value);


			auto next = suite::get_vec<BASE_POLICY>(2);
			next      = { index - 1, index - 2 };

			__gnu_parallel::for_each(next.begin(), next.end(), FIB_gnu{ m_policy });
		}
	};

	const auto b1_5_for_each_exponential_gnu = [](auto && policy, const auto & input_data) {
		// enable nested parallelism
		omp_set_nested(1);

		__gnu_parallel::for_each(input_data.begin(), input_data.end(), FIB_gnu{ policy });
	};

} // namespace B1

#endif //PSTL_BENCH_B1_5_FOR_EACH_EXPONENTIAL_GNU_H
