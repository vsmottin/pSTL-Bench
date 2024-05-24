#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_set_difference
{
	const auto set_difference_hpx = [](auto && policy, auto & data1, auto & data2, auto & output) {
		return hpx::set_difference(policy, data1.begin(), data1.end(), data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_difference
