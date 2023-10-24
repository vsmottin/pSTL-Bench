
#ifndef PSTL_BENCH_FOR_EACH_UTILS_H
#define PSTL_BENCH_FOR_EACH_UTILS_H

#include <cmath>

#include <ranges>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_for_each
{
	const auto kernel = [](const auto & input) {
		auto value = std::min(std::sin(input), std::tan(input));
		benchmark::DoNotOptimize(value);
	};

	template<class Policy, class Function>
	static void benchmark_for_each_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, data, kernel);)
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (int64_t(data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_UTILS_H
