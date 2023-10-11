
#ifndef PSTL_BENCH_FOR_EACH_UTILS_H
#define PSTL_BENCH_FOR_EACH_UTILS_H

#include <cmath>

#include <ranges>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_for_each
{
	const auto linear_kernel = [](const auto & input) {
		auto value = std::min(std::sin(input), std::tan(input));
#ifndef ONLY_GPU
		benchmark::DoNotOptimize(value);
#endif
	};

	const auto quadratic_kernel = [](const auto & e1, const auto & e2) {
		auto value = std::tan(e1) + std::cos(e2);
#ifndef ONLY_GPU
		benchmark::DoNotOptimize(value);
#endif
	};

	// calculating the 17 row of mandelbrot with an adjustable limit.
	// adjusted from https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc
	const auto mandelbrot_kernel = [](const auto & input, const double dx) {
		constexpr auto dy = (2) / (50 - 1);

		const auto     x = -2.0 + input * dx; // current real value
		constexpr auto y =
		    1.0 - 17 * dy; // current imaginary value, stays the same since only 17 row calucalted out of 50

		auto zReal = x;
		auto zImag = y;

		constexpr auto limit = 200;

		for (const std::weakly_incrementable auto i : std::views::iota(0, limit))
		{
			const auto r2 = zReal * zReal;
			const auto i2 = zImag * zImag;

			if (r2 + i2 > 4.0) return i;

			zImag = 2.0 * zReal * zImag + y;
			zReal = r2 - i2 + x;
		}

		return limit;
	};

	// adjusted from
	// https://github.com/dario-marvin/Mandelbrot/blob/master/Mandelbrot.cc
	const auto quadratic_mandelbrot_kernel = [](const auto real, const auto imag) {
		constexpr auto limit = 100;
		auto           zReal = real;
		auto           zImag = imag;

		for (int i = 0; i < limit; ++i)
		{
			const auto r2 = zReal * zReal;
			const auto i2 = zImag * zImag;

			if (r2 + i2 > 4.0) return i;

			zImag = 2.0 * zReal * zImag + imag;
			zReal = r2 - i2 + real;
		}
		return limit;
	};

	template<class Policy, class Function>
	static void benchmark_for_each_linear_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		auto x = suite::get_vec<Policy, suite::double_vec<Policy>>(state.range(0));
		suite::fill_init<Policy>(x, 1.0);

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, x, linear_kernel);)
		}
	}

	template<class Policy, class Function>
	static void benchmark_for_each_linear_mandelbrot_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		auto x = suite::get_vec<Policy, suite::double_vec<Policy>>(state.range(0));
		suite::fill_init<Policy>(x, 1.0);

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, x, mandelbrot_kernel);)
		}
	}

	template<class OuterPolicy, class InnerPolicy, class Function>
	static void benchmark_for_each_quadratic_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto outer_execution_policy = OuterPolicy{};
		constexpr auto inner_execution_policy = InnerPolicy{};

		const auto size       = state.range(0);
		const auto input_data = suite::generate_increment<InnerPolicy>(inner_execution_policy, size, 1);

		for (auto _ : state)
		{
			WRAP_TIMING(f(outer_execution_policy, inner_execution_policy, input_data, quadratic_kernel);)
		}
	}

	template<class OuterPolicy, class InnerPolicy, class Function>
	static void benchmark_for_each_quadratic_mandelbrot_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto outer_execution_policy = OuterPolicy{};
		constexpr auto inner_execution_policy = InnerPolicy{};

		const auto size       = state.range(0);
		const auto input_data = suite::generate_increment<InnerPolicy>(inner_execution_policy, size, 1);

		for (auto _ : state)
		{
			WRAP_TIMING(f(outer_execution_policy, inner_execution_policy, input_data, quadratic_mandelbrot_kernel);)
		}
	}

	template<class Policy, class Function>
	static void benchmark_for_each_exponential_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto size = state.range(0);
		const auto data = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _ : state)
		{
			WRAP_TIMING(f(execution_policy, data);)
		}
	}
} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_UTILS_H
