#ifndef PSTL_BENCH_COUNT_UTILS_H
#define PSTL_BENCH_COUNT_UTILS_H

#include <algorithm>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_count
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto input_data = suite::generate_increment(execution_policy, size, 1);

		static auto rd = std::random_device{};

		static std::minstd_rand               engine{ rd() };
		std::uniform_int_distribution<size_t> gen(0, input_data.size() - 1);

		for (auto _ : state)
		{
			const auto value = gen(engine);

			WRAP_TIMING(const auto res = F(execution_policy, input_data, value);)

			assert((res == 1));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_count

#endif //PSTL_BENCH_COUNT_UTILS_H
