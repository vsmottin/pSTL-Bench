#pragma once

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include "pstl/utils/utils.h"

namespace benchmark_any_of
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
		std::uniform_int_distribution<size_t> gen(0, input_data.size() - 1);

		for (auto _ : state)
		{
			const auto index = gen(engine);
			const auto value = input_data[index];

			const auto output = pstl::wrap_timing(state, std::forward<Function>(F), execution_policy, input_data,
			                                      [=](const auto & val) { return val == value; });

			assert(pstl::are_equivalent(output, true));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}

} // namespace benchmark_any_of


