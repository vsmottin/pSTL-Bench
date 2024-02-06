#ifndef PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H
#define PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_exclusive_scan
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		std::exclusive_scan(std::execution::seq, input_data.begin(), input_data.end(), output.begin(),
		                    typename std::iterator_traits<decltype(input_data.begin())>::value_type{});

		const auto solution = output.back();

		for (auto _ : state)
		{
			WRAP_TIMING(F(execution_policy, input_data, output);)

			assert(pstl::are_equivalent(output.back(), solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data, output));
	}
} // namespace benchmark_exclusive_scan

#endif //PSTL_BENCH_EXCLUSIVE_SCAN_UTILS_H
