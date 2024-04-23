#ifndef PSTL_BENCH_SORT_UTILS_H
#define PSTL_BENCH_SORT_UTILS_H

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_sort
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && f)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto input_data = pstl::generate_increment(execution_policy, size);

		static std::random_device rd;
		static std::mt19937       generator(rd());

		for (auto _ : state)
		{
			std::shuffle(input_data.begin(), input_data.end(), generator);

			WRAP_TIMING([&]() {
				f(execution_policy, input_data);
#ifdef USE_GPU
				pstl::elem_t i = 1;
				std::for_each(input_data.begin(), input_data.end(), [&](auto & elem) { elem = i++; });
#endif
			}())

			// assert(std::is_sorted(input_data.begin(), input_data.end()));
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, input_data));
	}
} // namespace benchmark_sort

#endif //PSTL_BENCH_SORT_UTILS_H
