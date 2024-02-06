#ifndef PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H
#define PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_inclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		std::inclusive_scan(std::execution::seq, input_data.begin(), input_data.end(), output.begin());

		const auto solution = output.back();

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)

			assert((output.back() == solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_inclusive_scan

#endif //PSTL_BENCH_INCLUSIVE_SCAN_UTILS_H
