#ifndef PSTL_BENCH_MIN_ELEMENT_UTILS_H
#define PSTL_BENCH_MIN_ELEMENT_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_min_element
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment(execution_policy, size, 1);
		std::shuffle(input_data.begin(), input_data.end(), std::mt19937{ std::random_device{}() });

		const auto solution = std::min_element(input_data.begin(), input_data.end());

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = F(execution_policy, input_data);)

			assert((solution == output));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_min_element

#endif //PSTL_BENCH_MIN_ELEMENT_UTILS_H
