
#ifndef PSTL_BENCH_B9_UTILS_H
#define PSTL_BENCH_B9_UTILS_H

#include <benchmark/benchmark.h>

#include <execution>
#include <vector>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

namespace B9 {
	auto lambda = [] (const auto & x) { return x + 10; };

	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);
		const auto last_element = size - 1;

		const auto input_data = suite::generate_uniform_dist_vec<Policy>(size, 0, 10);

		auto res = suite::get_vec<Policy>(size);

		for ([[maybe_unused]] auto _: state) {
			WRAP_TIMING(F(execution_policy, input_data, res, lambda);)

			assert((res[0] == lambda(input_data[0])));
			assert((res[last_element] == lambda(input_data[last_element])));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) * (2 * int64_t(input_data.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
}

#endif //PSTL_BENCH_B9_UTILS_H
