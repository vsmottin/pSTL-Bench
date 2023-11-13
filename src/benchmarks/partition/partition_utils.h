#ifndef PSTL_BENCH_PARTITION_UTILS_H
#define PSTL_BENCH_PARTITION_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_partition
{
	const auto condition = [](const auto & i) {
		return i % 2 == 0;
	};

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), std::mt19937(std::random_device()()));

			WRAP_TIMING(F(execution_policy, input_data, condition);)

			assert(std::is_partitioned(input_data.begin(), input_data.end(), condition));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_partition

#endif //PSTL_BENCH_PARTITION_UTILS_H
