#ifndef PSTL_BENCH_SORT_UTILS_H
#define PSTL_BENCH_SORT_UTILS_H

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment<Policy>(execution_policy, size, 1);

		static std::random_device rd;
		static std::mt19937       generator(rd());

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), generator);

			WRAP_TIMING(f(execution_policy, input_data))

			assert(std::is_sorted(input_data.begin(), input_data.end()));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_UTILS_H
