#pragma once

#include <execution>
#include <numeric>

namespace benchmark_set_difference
{
	const auto set_difference_std = [](auto && policy, auto & data1, auto & data2, auto & output) {
		return std::set_difference(policy, data1.begin(), data1.end(), data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_difference
