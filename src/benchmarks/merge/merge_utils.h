#ifndef PSTL_BENCH_MERGE_UTILS_H
#define PSTL_BENCH_MERGE_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_merge
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);
		auto output     = input_data;

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), std::mt19937{ std::random_device{}() });

			auto middle = input_data.begin() + (input_data.size() / 2);

			std::sort(input_data.begin(), middle);
			std::sort(middle, input_data.end());

			WRAP_TIMING(F(execution_policy, input_data.begin(), middle, middle, input_data.end(), output.begin());)

			assert((std::is_sorted(output.begin(), output.end())));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_merge

#endif //PSTL_BENCH_MERGE_UTILS_H
