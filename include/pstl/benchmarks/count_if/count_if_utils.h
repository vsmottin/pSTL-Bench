#ifndef PSTL_BENCH_COUNT_IF_UTILS_H
#define PSTL_BENCH_COUNT_IF_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_count_if
{
	const auto condition = [](const auto & i) {
		// Check if the number is even
		if constexpr (std::is_integral_v<decltype(i)>) { return i % 2 == 0; }
		else { return static_cast<int>(i) % 2 == 0; }
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = pstl::generate_increment(execution_policy, size);

		const auto solution = std::count_if(input_data.begin(), input_data.end(), condition);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto res = F(execution_policy, input_data, condition);)

			assert(pstl::are_equivalent(res, solution));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_count_if

#endif //PSTL_BENCH_COUNT_IF_UTILS_H
