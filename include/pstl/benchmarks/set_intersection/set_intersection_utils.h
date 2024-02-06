#ifndef PSTL_BENCH_SET_INTERSECTION_UTILS_H
#define PSTL_BENCH_SET_INTERSECTION_UTILS_H

#include <numeric>

#include <benchmark/benchmark.h>

#include "pstl/utils.h"

namespace benchmark_set_intersection
{
	template<class Policy, class Function>
	static void benchmark_wrapper(benchmark::State & state, Function && F)
	{
		constexpr auto execution_policy = Policy{};

		const auto & size = state.range(0);

		auto data1 = pstl::generate_increment(execution_policy, size);
		auto data2 =
		    pstl::generate_increment(execution_policy, size / 2, static_cast<decltype(data1)::value_type>(size / 4),
		                             static_cast<decltype(data1)::value_type>(1));

		const auto max_size = std::min(data1.size(), data2.size());

		auto result = std::vector<typename decltype(data1)::value_type>(
		    max_size, std::numeric_limits<typename decltype(data1)::value_type>::quiet_NaN());
		auto output = result;

		std::ignore = std::set_intersection(data1.begin(), data1.end(), data2.begin(), data2.end(), result.begin());
		std::sort(result.begin(), result.end());

		for (auto _ : state)
		{
			WRAP_TIMING(std::ignore = F(execution_policy, data1.begin(), data1.end(), data2.begin(), data2.end(),
			                            output.begin());)

			std::sort(output.begin(), output.end());

			assert(std::equal(result.begin(), result.end(), output.begin(), output.end()));

			std::fill(output.begin(), output.end(),
			          std::numeric_limits<typename decltype(data1)::value_type>::quiet_NaN());
		}

		state.SetBytesProcessed(pstl::computed_bytes(state, data1, data2));
	}
} // namespace benchmark_set_intersection

#endif //PSTL_BENCH_SET_INTERSECTION_UTILS_H
