#pragma once

#include <parallel/algorithm>

namespace benchmark_set_intersection
{
	const auto set_intersection_gnu = []([[maybe_unused]] auto && policy, auto first1, auto last1, auto first2,
	                                     auto last2, auto d_first) {
		return __gnu_parallel::set_intersection(first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_set_intersection


