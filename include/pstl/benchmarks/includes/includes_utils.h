#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_includes
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		const auto subset = pstl::generate_increment(execution_policy, size / 2, static_cast<pstl::elem_t>(size / 4),
		                                             static_cast<pstl::elem_t>(1));

		const auto solution = std::includes(input_data.begin(), input_data.end(), subset.begin(), subset.end());

		for (auto _ : state)
		{
			const auto output =
			    pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data, subset);
			assert(pstl::are_equivalent(output, solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data, subset));
	}
} // namespace benchmark_includes


