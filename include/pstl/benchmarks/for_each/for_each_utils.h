
#ifndef PSTL_BENCH_FOR_EACH_UTILS_H
#define PSTL_BENCH_FOR_EACH_UTILS_H

#include <cmath>

#include "pstl/utils.h"
#include <benchmark/benchmark.h>

namespace benchmark_for_each
{
	const auto empty_kernel = [](auto & input) {
		benchmark::DoNotOptimize(input);
	};

	const auto active_wait_kernel = [](auto & input) {
		benchmark::DoNotOptimize(input);

		using namespace std::chrono_literals;

		std::chrono::nanoseconds ns(0);

		const auto start  = std::chrono::high_resolution_clock::now();
		const auto target = start + 1ns;

		// Active wait
		while (std::chrono::high_resolution_clock::now() < target)
		{
			benchmark::DoNotOptimize(input);
		}
	};

	const auto inv_sqrt_kernel = [](auto & input) {
		// Fast inverse square root from Quake III Arena
		// Modern C++ version
		// https://en.wikipedia.org/wiki/Fast_inverse_square_root

		const float number = input;

		union
		{
			float    f;
			uint32_t i;
		} conv = { .f = number };
		conv.i = 0x5f3759df - (conv.i >> 1);
		conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);

		input = conv.f;

		benchmark::DoNotOptimize(input);
	};

	template<class Policy, class Function, class Kernel>
	static void benchmark_for_each_wrapper(benchmark::State & state, Function && f, Kernel && kernel)
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
