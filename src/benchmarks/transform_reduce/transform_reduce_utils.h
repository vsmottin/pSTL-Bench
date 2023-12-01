
#ifndef PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H
#define PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H

#include <cmath>

#include <benchmark/benchmark.h>
#include <benchmark_utils.h>

namespace benchmark_transform_reduce
{
	const auto transform_kernel = [](const auto & input) {
		return input * input;
	};

	template<class Policy, class Function>
	static void benchmark_transform_reduce_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = suite::generate_increment<Policy>(execution_policy, size, 1);

		using T = decltype(input_data)::value_type;

		const auto solution =
		    std::transform_reduce(input_data.begin(), input_data.end(), T{}, std::plus<>(), transform_kernel);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = f(execution_policy, input_data, transform_kernel);)
			if (solution != output)
			{
				std::cerr << "ERROR: solution != output (" << solution << " != " << output << ")" << std::endl;
			}
			assert(solution == output);
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H
