#ifndef PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H
#define PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_inclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		auto solution = input_data;
		std::fill(solution.begin(), solution.end(), 0);

		auto output = solution;

		std::inclusive_scan(std::execution::seq, input_data.begin(), input_data.end(), solution.begin());

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)

			assert((output.back() == solution.back()));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_inclusive_scan

#endif //PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H
