#ifndef PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H
#define PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_lexicographical_compare
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto data1 = pstl::generate_increment(execution_policy, size);
		const auto data2 = pstl::generate_increment(execution_policy, size);

		const auto result = std::lexicographical_compare(data1.begin(), data1.end(), data2.begin(), data2.end());

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, data1, data2);)

			assert(pstl::are_equivalent(result, output));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, data1, data2));
	}
} // namespace benchmark_lexicographical_compare

#endif //PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_UTILS_H
