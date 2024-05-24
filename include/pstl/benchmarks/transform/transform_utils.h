
#pragma once

#include <cmath>

#include "pstl/utils/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_transform
{
	const auto kernel = [](const auto & input) {
		return std::min(std::sin(input), std::tan(input));
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input_data, kernel);
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_transform


