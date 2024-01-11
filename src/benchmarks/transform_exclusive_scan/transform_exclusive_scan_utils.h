
#ifndef PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_UTILS_H
#define PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_UTILS_H

#include <cmath>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_transform_exclusive_scan
{
	const auto kernel = [](const auto & input) {
		return input * input;
	};

	template<class Policy, class Function>
	static void benchmark_transform_exclusive_scan_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment<Policy>(execution_policy, size, 1);

		auto output = input_data;
		std::fill(output.begin(), output.end(), 0);

		const auto solution = std::transform_exclusive_scan(input_data.begin(), input_data.end(),
		                                                    output.begin(), 0, std::plus<>(), kernel);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto result = f(execution_policy, input_data, output, kernel);)
			assert(result == solution);
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_transform_exclusive_scan

#endif //PSTL_BENCH_TRANSFORM_EXCLUSIVE_SCAN_UTILS_H
