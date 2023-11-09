#ifndef PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H
#define PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_lexicographical_compare
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto data_a = suite::generate_increment(execution_policy, size, 1);
		const auto data_b = suite::generate_increment(execution_policy, size, 1);

		const auto result = std::lexicographical_compare(data_a.begin(), data_a.end(), data_b.begin(), data_b.end());

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, data_a, data_b);)

			assert((result == output));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(data_a.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_lexicographical_compare

#endif //PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H
