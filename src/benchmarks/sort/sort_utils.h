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

		auto input = suite::generate_increment<Policy>(execution_policy, size, 1);

		static std::random_device rd;
		static std::mt19937       generator(rd());

		for (auto _ : state)
		{
			std::shuffle(input.begin(), input.end(), generator);

			WRAP_TIMING(f(execution_policy, input))

			assert(std::is_sorted(input.begin(), input.end()));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (int64_t(input.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_UTILS_H
