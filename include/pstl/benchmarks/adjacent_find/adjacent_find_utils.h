#pragma once

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_adjacent_find
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		static auto rd = std::random_device{};

		// Choose a random number between 1 and size
		static std::minstd_rand               engine{ rd() };
		std::uniform_int_distribution<size_t> gen(0, input_data.size() - 2);

		for (auto _ : state)
		{
			const auto index  = gen(engine);
			input_data[index] = input_data[index + 1];

			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data);

			const auto solution = input_data.begin() + index;

			assert(pstl::are_equivalent(output, solution));

			input_data[index] = input_data[index + 1] - 1;
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_adjacent_find


