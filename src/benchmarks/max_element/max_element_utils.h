#ifndef PSTL_BENCH_MAX_ELEMENT_UTILS_H
#define PSTL_BENCH_MAX_ELEMENT_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_max_element
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);
		std::shuffle(input_data.begin(), input_data.end(), std::mt19937{ std::random_device{}() });

		const auto solution = std::max_element(input_data.begin(), input_data.end());

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, input_data);)

			assert((solution == output));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * int64_t(input_data.size());

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
} // namespace benchmark_max_element

#endif //PSTL_BENCH_MAX_ELEMENT_UTILS_H
