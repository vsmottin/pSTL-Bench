
#ifndef PSTL_BENCH_FOR_EACH_UTILS_H
#define PSTL_BENCH_FOR_EACH_UTILS_H

#include <cmath>

#include "pstl/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_for_each
{
	const auto kernel = [](auto & input) {
		benchmark::DoNotOptimize(input);

		using namespace std::chrono_literals;

		std::chrono::nanoseconds ns(0);

		const auto start  = std::chrono::high_resolution_clock::now();
		const auto target = start + 1ns;

		// Active wait
		while (std::chrono::high_resolution_clock::now() < target) {}

		benchmark::DoNotOptimize(input);
	};

	template<class Policy, class Function>
	static void benchmark_for_each_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data = pstl::generate_increment(execution_policy, size);

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, data, kernel);)
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, data));
	}
} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_UTILS_H
