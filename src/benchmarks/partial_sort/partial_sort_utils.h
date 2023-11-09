#ifndef PSTL_BENCH_PARTIAL_SORT_UTILS_H
#define PSTL_BENCH_PARTIAL_SORT_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_partial_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), std::mt19937{ std::random_device{}() });

			auto middle = input_data.begin() + (input_data.size() / 2);

			WRAP_TIMING(F(execution_policy, input_data.begin(), middle, input_data.end());)

			assert((std::is_sorted(input_data.begin(), middle)));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * int64_t(input_data.size());

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_partial_sort

#endif //PSTL_BENCH_PARTIAL_SORT_UTILS_H
