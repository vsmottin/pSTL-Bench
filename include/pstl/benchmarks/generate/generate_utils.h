#pragma once

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_generate
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		static const auto generator = []() {
			return pstl::elem_t{};
		};

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data, generator);
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_generate


