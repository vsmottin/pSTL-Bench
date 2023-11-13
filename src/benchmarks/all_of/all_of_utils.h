#ifndef PSTL_BENCH_ALL_OF_UTILS_H
#define PSTL_BENCH_ALL_OF_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_all_of
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		const auto condition = [](const auto & val) {
			return val > 0;
		};

		const auto solution = std::all_of(input_data.begin(), input_data.end(), condition);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, input_data, condition);)

			assert((output == solution));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_all_of

#endif //PSTL_BENCH_ALL_OF_UTILS_H
