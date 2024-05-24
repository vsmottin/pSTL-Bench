#pragma once

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_reduce
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		const auto solution = std::accumulate(input_data.begin(), input_data.end(), pstl::elem_t{});

		for (auto _ : state)
		{
			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy,
			                                      input_data.begin(), input_data.end());

			assert(pstl::are_equivalent(output, solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_reduce


