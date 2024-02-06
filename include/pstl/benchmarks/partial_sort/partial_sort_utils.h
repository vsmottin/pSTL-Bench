#ifndef PSTL_BENCH_PARTIAL_SORT_UTILS_H
#define PSTL_BENCH_PARTIAL_SORT_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_partial_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), std::mt19937{ std::random_device{}() });

			auto middle = input_data.begin() + (input_data.size() / 2);

			WRAP_TIMING(F(execution_policy, input_data.begin(), middle, input_data.end());)

			assert((std::is_sorted(input_data.begin(), middle)));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_partial_sort

#endif //PSTL_BENCH_PARTIAL_SORT_UTILS_H
