#pragma once

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		static std::random_device rd;
		static std::mt19937       generator(rd());

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), generator);

			pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input_data.begin(), input_data.end());

			assert(std::is_sorted(input_data.begin(), input_data.end()));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_sort


