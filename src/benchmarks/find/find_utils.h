#ifndef PSTL_BENCH_FIND_UTILS_H
#define PSTL_BENCH_FIND_UTILS_H

#include <cassert>
#include <random>

#include <benchmark/benchmark.h>

#include <benchmark_utils.h>

namespace benchmark_find
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		// vector with values [0,size)
		const auto input_data = suite::generate_increment<Policy>(execution_policy, size, 1);

		const auto get_value = [](const auto & vec) {
			// Seed with a real random value, if available
			static std::random_device             rd;
			// Choose a random number between 1 and size
			static std::minstd_rand               engine{ rd() };
			std::uniform_int_distribution<size_t> gen(0, vec.size() - 1);

			const auto index = gen(engine);

			return vec[index];
		};

		for (auto _ : state)
		{
			// random value in [0,size)
			const auto value = get_value(input_data);

			WRAP_TIMING(auto find_location = F(execution_policy, input_data, value);)

			// make sure the val is really found
			assert(find_location == std::find(input_data.begin(), input_data.end(), value));
		}

		state.SetBytesProcessed(suite::computed_bytes(state, input_data));
	}
} // namespace benchmark_find

#endif //PSTL_BENCH_FIND_UTILS_H
