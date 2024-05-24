#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_search
{
	const auto search_hpx = [](auto && policy, const auto & data1, const auto & data2) {
		return hpx::search(policy, data1.begin(), data1.end(), data2.begin(), data2.end());
	};
} // namespace benchmark_search


