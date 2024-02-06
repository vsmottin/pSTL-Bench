#ifndef PSTL_BENCH_GENERATE_UTILS_H
#define PSTL_BENCH_GENERATE_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_generate
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		static const auto generator = []() {
			return 0;
		};

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, generator);)
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_generate

#endif //PSTL_BENCH_GENERATE_UTILS_H
