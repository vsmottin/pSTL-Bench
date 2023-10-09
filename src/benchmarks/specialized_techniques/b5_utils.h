#ifndef PSTL_BENCH_B5_UTILS_H
#define PSTL_BENCH_B5_UTILS_H

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace B5 {
	template<class Policy, class Function>
	static void benchmark_find_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _: state) {
			WRAP_TIMING(auto find_location = F(execution_policy, vec1, 0);)

			// make sure the val is really found
			assert(find_location != vec1.end());
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_find_last_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto &size = state.range(0);

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _: state) {
			WRAP_TIMING(auto find_location = F(execution_policy, vec1, size - 1);)

			// make sure the val is really found
			assert(find_location != vec1.end());
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_find_non_existing_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		const auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1);

		for (auto _: state) {
			WRAP_TIMING(auto find_location = F(execution_policy, vec1, -10);)

			// make sure the val is really found
			assert(find_location == vec1.end());
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_partition_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		auto vec1 = suite::generate_increment(execution_policy, size, 1);

		for (auto _: state) {
			WRAP_TIMING(F(execution_policy, vec1);)
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()) + int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_unique_copy_default_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with value 1 of length size
		auto vec1 = suite::get_vec<Policy>(size);
		suite::fill_init<Policy>(vec1, 1);

		auto result = suite::get_vec<Policy>(1);
		suite::fill_init<Policy>(result, 0);

		for (auto _: state) {
			WRAP_TIMING(F(execution_policy, vec1, result);)

			// simple check so the val will not be optimized aways
			assert(result.size() == 1 && result[0] == 1);
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()) + int64_t(result.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_minmax_element_all_equal_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with value 1
		auto vec1 = suite::generate_increment<Policy>(execution_policy, size, 1, 0);

		for (auto _: state) {
			WRAP_TIMING(const auto res = F(execution_policy, vec1);)

			// min = max = 1 because all elements are 1
			assert(*(res.first) == 1 && *(res.second) == 1);
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}

	template<class Policy, class Function>
	static void benchmark_minmax_element_increasing_wrapper (benchmark::State & state, Function && F) {
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with value 1
		auto vec1 = suite::generate_increment(execution_policy, size, 1);

		for (auto _: state) {
			WRAP_TIMING(const auto res = F(execution_policy, vec1);)

			// min = max = 1 because all elements are 1
			assert(*(res.first) == 0 && *(res.second) == size - 1);
		}

		// https://ccfd.github.io/courses/hpc_lab01.html
		const int64_t actual_size_in_bytes = sizeof(int) *
											 (int64_t(vec1.size()));

		state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
	}
}

#endif //PSTL_BENCH_B5_UTILS_H
