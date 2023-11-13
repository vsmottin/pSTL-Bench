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

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_reduce

#endif //PSTL_BENCH_REDUCE_UTILS_H
