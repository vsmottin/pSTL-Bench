
#ifndef PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H
#define PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H

#include <cmath>

#include "pstl/utils.h"
#include <benchmark/benchmark.h>

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

		auto input_data = pstl::generate_increment(execution_policy, size);

		const auto solution = std::transform_reduce(std::execution::seq, input_data.cbegin(), input_data.cend(),
		                                            pstl::elem_t{}, std::plus<>(), transform_kernel);

		for (auto _ : state)
		{
			WRAP_TIMING(const auto output = f(execution_policy, input_data, transform_kernel);)

			assert(pstl::are_equivalent(solution, output));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_transform_reduce

#endif //PSTL_BENCH_TRANSFORM_REDUCE_UTILS_H
