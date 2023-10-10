#ifndef PSTL_BENCH_REDUCE_UTILS_H
#define PSTL_BENCH_REDUCE_UTILS_H

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_reduce
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		const auto solution = std::accumulate(input_data.begin(), input_data.end(), 0);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto res = F(execution_policy, input_data);)

			assert((res == solution));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_reduce

#endif //PSTL_BENCH_REDUCE_UTILS_H
