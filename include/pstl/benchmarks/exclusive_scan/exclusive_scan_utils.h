#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_exclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		std::exclusive_scan(std::execution::seq, input_data.begin(), input_data.end(), output.begin(), pstl::elem_t{});

		const auto solution = output.back();

		for (auto _ : state)
		{
			pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data, output);

			assert(pstl::are_equivalent(output.back(), solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data, output));
	}
} // namespace benchmark_exclusive_scan


