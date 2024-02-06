#ifndef PSTL_BENCH_SET_INTERSECTION_STD_H
#define PSTL_BENCH_SET_INTERSECTION_STD_H

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_set_intersection
{
	const auto set_intersection_std = [](auto && policy, const auto & first1, const auto & last1, const auto & first2,
	                                     const auto & last2, auto && d_first) {
		return std::set_intersection(policy, first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_set_intersection

#endif //PSTL_BENCH_SET_INTERSECTION_STD_H
