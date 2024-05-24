#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_set_intersection
{
	const auto set_intersection_hpx = [](auto && policy,  const auto & data1, const auto & data2,
					   auto & output) {
		return hpx::set_intersection(policy, data1.begin(), data1.end(), data2.begin(), data2.end(), output.begin());
	};
} // namespace benchmark_set_intersection
