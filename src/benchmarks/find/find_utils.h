#ifndef PSTL_BENCH_FIND_UTILS_H
#define PSTL_BENCH_FIND_UTILS_H

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_find
{
	template<class Policy, class Function, class TargetValueF>
	static void benchmark_find_wrapper_template(benchmark::State & state, Function && F, const TargetValueF & get_value)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _ : state)
		{
			// random value in [0,size)
			const auto value = get_value(vec1);

			WRAP_TIMING(auto find_location = F(execution_policy, vec1, value);)

			// make sure the val is really found
			assert(find_location == std::find(vec1.begin(), vec1.end(), value));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_find_random_wrapper(benchmark::State & state, Function && F)
	{
		benchmark_find_wrapper_template<Policy, Function>(state, F, [](const auto & vec) {
			// Seed with a real random value, if available
			static std::random_device rd;

			// Choose a random number between 1 and size
			static std::minstd_rand               engine{ rd() };
			std::uniform_int_distribution<size_t> gen(0, vec.size() - 1);

			const auto index = gen(engine);

			return vec[index];
		});
	}

	template<class Policy, class Function>
	static void benchmark_find_first_wrapper(benchmark::State & state, Function && F)
	{
		benchmark_find_wrapper_template<Policy, Function>(state, F, [](const auto & vec) { return vec.front(); });
	}

	template<class Policy, class Function>
	static void benchmark_find_last_wrapper(benchmark::State & state, Function && F)
	{
		benchmark_find_wrapper_template<Policy, Function>(state, F, [](const auto & vec) { return vec.back(); });
	}

	template<class Policy, class Function>
	static void benchmark_find_non_existing_wrapper(benchmark::State & state, Function && F)
	{
		benchmark_find_wrapper_template<Policy, Function>(state, F,
		                                                  []([[maybe_unused]] const auto & vec) { return -1; });
	}

} // namespace benchmark_find

#endif //PSTL_BENCH_FIND_UTILS_H
