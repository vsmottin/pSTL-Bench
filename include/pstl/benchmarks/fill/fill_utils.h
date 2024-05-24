#pragma once

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

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
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data, pstl::elem_t{});
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_fill


