#ifndef PSTL_BENCH_COUNT_IF_UTILS_H
#define PSTL_BENCH_COUNT_IF_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_count_if
{
	const auto condition = [](const auto & i) {
		return i % 2 == 0;
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		const auto solution = std::count_if(input_data.begin(), input_data.end(), condition);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto res = F(execution_policy, input_data, condition);)

			assert((res == solution));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_count_if

#endif //PSTL_BENCH_COUNT_IF_UTILS_H
