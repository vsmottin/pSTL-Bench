#ifndef PSTL_BENCH_INCLUDES_UTILS_H
#define PSTL_BENCH_INCLUDES_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_includes
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		const auto subset = suite::generate_increment(execution_policy, size / 2, size / 2);

		const auto solution = std::includes(input_data.begin(), input_data.end(), subset.begin(), subset.end());

		for (auto _ : state)
		{
			WRAP_TIMING(auto output = F(execution_policy, input_data, subset);)

			benchmark::DoNotOptimize(output);

			assert((output == solution));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data, subset));
	}
} // namespace benchmark_includes

#endif //PSTL_BENCH_INCLUDES_UTILS_H
