#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_UTILS_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_adjacent_difference
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		std::adjacent_difference(std::execution::seq, input_data.begin(), input_data.end(), output.begin());

		const auto solution = output.back();

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)

			assert((output.back() == solution));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_adjacent_difference

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_UTILS_H
