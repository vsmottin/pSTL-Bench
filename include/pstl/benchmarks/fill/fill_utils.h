#ifndef PSTL_BENCH_FILL_UTILS_H
#define PSTL_BENCH_FILL_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_fill
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, 0);)
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_fill

#endif //PSTL_BENCH_FILL_UTILS_H
