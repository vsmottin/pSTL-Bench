#ifndef PSTL_BENCH_GENERATE_UTILS_H
#define PSTL_BENCH_GENERATE_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_generate
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		static const auto generator = []() { return 0; };

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, generator);)
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_generate

#endif //PSTL_BENCH_GENERATE_UTILS_H
