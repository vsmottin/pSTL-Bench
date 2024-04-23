#ifndef PSTL_BENCH_SEARCH_UTILS_H
#define PSTL_BENCH_SEARCH_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_search
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto data1 = pstl::generate_increment(execution_policy, size);
		const auto data2 = pstl::generate_increment(execution_policy, size / 2, static_cast<pstl::elem_t>(size / 4),
		                                            static_cast<pstl::elem_t>(1));

		const auto result = std::search(data1.begin(), data1.end(), data2.begin(), data2.end());

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output =
			                F(execution_policy, data1.begin(), data1.end(), data2.begin(), data2.end());)

			assert(pstl::are_equivalent(result, output));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, data1, data2));
	}
} // namespace benchmark_search

#endif //PSTL_BENCH_SEARCH_UTILS_H
