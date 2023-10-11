#ifndef PSTL_BENCH_FOR_EACH_GNU_EXPONENTIAL_H
#define PSTL_BENCH_FOR_EACH_GNU_EXPONENTIAL_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>

#include <parallel/algorithm>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_for_each
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

	const auto for_each_gnu_exponential = [](auto && policy, const auto & input_data) {
		// enable nested parallelism
		omp_set_nested(1);

		__gnu_parallel::for_each(input_data.begin(), input_data.end(), FIB_gnu{ policy });
	};

} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_GNU_EXPONENTIAL_H
