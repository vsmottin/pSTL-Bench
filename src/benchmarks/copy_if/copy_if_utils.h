#ifndef PSTL_BENCH_COPY_IF_UTILS_H
#define PSTL_BENCH_COPY_IF_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_copy_if
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		auto output = input_data;

		const auto condition = [](const auto & value) {
			return value % 2 == 0;
		};

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output, condition);)
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data, output));
	}
} // namespace benchmark_copy_if

#endif //PSTL_BENCH_COPY_IF_UTILS_H
