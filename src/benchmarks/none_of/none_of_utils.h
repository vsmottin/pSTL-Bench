#ifndef PSTL_BENCH_NONE_OF_UTILS_H
#define PSTL_BENCH_NONE_OF_UTILS_H

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_none_of
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		const auto condition = [=](const auto & val) {
			return val > size;
		};

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, input_data, condition);)

			assert((output == true));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}

} // namespace benchmark_none_of

#endif //PSTL_BENCH_NONE_OF_UTILS_H
