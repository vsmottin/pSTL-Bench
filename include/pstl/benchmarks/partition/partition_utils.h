#pragma once

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_partition
{
	const auto condition = [](const auto & i) {
		// Check if the number is even
		if constexpr (std::is_integral_v<decltype(i)>) { return i % 2 == 0; }
		else { return static_cast<int>(i) % 2 == 0; }
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), std::mt19937(std::random_device()()));

			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data.begin(), input_data.end(),
			                  condition);

			assert(std::is_partitioned(input_data.begin(), input_data.end(), condition));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_partition


