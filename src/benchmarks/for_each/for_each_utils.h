
#ifndef PSTL_BENCH_FOR_EACH_UTILS_H
#define PSTL_BENCH_FOR_EACH_UTILS_H

#include <cmath>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_for_each
{
	const auto kernel = [](const auto & input) {
		auto value = std::min(std::sin(input), std::tan(input));
#ifndef USE_GPU
		benchmark::DoNotOptimize(value);
#endif
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

		state.SetBytesProcessed(suite::computed_bytes(state, data));
	}
} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_UTILS_H
