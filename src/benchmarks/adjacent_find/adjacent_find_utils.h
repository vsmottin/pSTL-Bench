#ifndef PSTL_BENCH_ADJACENT_FIND_UTILS_H
#define PSTL_BENCH_ADJACENT_FIND_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_adjacent_find
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		static auto rd = std::random_device{};

		// Choose a random number between 1 and size
		static std::minstd_rand               engine{ rd() };
		std::uniform_int_distribution<size_t> gen(0, input_data.size() - 2);

		for (auto _ : state)
		{
			const auto index  = gen(engine);
			input_data[index] = input_data[index + 1];

			WRAP_TIMING(const auto output = F(execution_policy, input_data);)

			const auto solution = input_data.begin() + index;

			assert((output == solution));

			input_data[index] = input_data[index + 1] - 1;
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_adjacent_find

#endif //PSTL_BENCH_ADJACENT_FIND_UTILS_H
