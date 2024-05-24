#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_set_intersection
{
	const auto set_intersection_std = [](auto && policy, const auto & data1, const auto & data2, auto & output) {
		return std::set_intersection(policy, data1.begin(), data1.end(), data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_intersection
