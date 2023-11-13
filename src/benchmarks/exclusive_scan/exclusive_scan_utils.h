#ifndef PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H
#define PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_exclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		std::exclusive_scan(std::execution::seq, input_data.begin(), input_data.end(), output.begin(), 0);

		const auto solution = output.back();

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)

			assert((output.back() == solution));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data, output));
	}
} // namespace benchmark_exclusive_scan

#endif //PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H
