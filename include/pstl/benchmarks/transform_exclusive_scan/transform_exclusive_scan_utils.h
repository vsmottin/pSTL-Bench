
#pragma once

#include <cmath>

#include "pstl/utils/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_transform_exclusive_scan
{
	const auto kernel = [](const auto & input) {
		return input * input;
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		const auto solution = std::transform_inclusive_scan(std::execution::seq, input_data.begin(), input_data.end(),
		                                                    output.begin(), std::plus<>(), kernel);

		for (auto _ : state)
		{
			const auto result =
			    pstl::wrap_timing(state, std::forward<Function>(f), execution_policy, input_data, output, kernel);
			assert(pstl::are_equivalent(result, solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_transform_exclusive_scan


