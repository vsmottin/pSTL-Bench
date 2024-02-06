#ifndef PSTL_BENCH_COPY_UTILS_H
#define PSTL_BENCH_COPY_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_copy
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		auto output = input_data;

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data, output));
	}
} // namespace benchmark_copy

#endif //PSTL_BENCH_COPY_UTILS_H
