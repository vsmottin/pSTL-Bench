#pragma once

#include <parallel/algorithm>

namespace benchmark_set_intersection
{
	const auto set_intersection_gnu = []([[maybe_unused]] auto && policy, auto & data1, auto & data2, auto & output) {
		return __gnu_parallel::set_intersection(data1.begin(), data1.end(), data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_intersection
