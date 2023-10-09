
#ifndef PSTL_BENCH_B6_UTILS_H
#define PSTL_BENCH_B6_UTILS_H

#include <benchmark/benchmark.h>

#include <execution>

#include <benchmark_utils.h>

namespace B6 {
	template<class Policy, class Function>
	static void benchmark_inclusive_scan_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		const auto solution = size * (0 + (size - 1)) / 2;

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment(execution_policy, size, 1);

		auto res = suite::get_vec<Policy>(vec1.size());

		for (auto _: state) {
			WRAP_TIMING(F(execution_policy, vec1, res);)

			assert(res[size - 1] = solution);
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()) + int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_exclusive_scan_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment(execution_policy, size, 1);

		auto res = suite::get_vec<Policy>(vec1.size());

		for (auto _: state) {
			WRAP_TIMING(F(execution_policy, vec1, res);)

			assert((res[0] == 0));
			assert((res[1] == vec1[0]));
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()) + int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
}

#endif //PSTL_BENCH_B6_UTILS_H
