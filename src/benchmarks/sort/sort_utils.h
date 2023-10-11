#ifndef PSTL_BENCH_SORT_UTILS_H
#define PSTL_BENCH_SORT_UTILS_H

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_sort
{
	template<class Policy, class Function, class Input>
	void benchmark_sort_template(benchmark::State & state, Function && f, Input & input)
	{
		constexpr auto execution_policy = Policy{};

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, input))

			assert(std::is_sorted(input.begin(), input.end()));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (int64_t(input.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	void already_sorted_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto already_sorted_vec = suite::generate_increment<Policy>(execution_policy, size, 1);

		benchmark_sort_template<Policy>(state, F, already_sorted_vec);
	}

	template<class Policy, class Function>
	void random_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto random_vec = suite::generate_increment<Policy>(execution_policy, size, 1);

		std::random_shuffle(random_vec.begin(), random_vec.end());

		benchmark_sort_template<Policy>(state, F, random_vec);
	}
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_UTILS_H
