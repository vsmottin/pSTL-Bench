#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_all_of
{
	const auto all_of_hpx = [](auto && policy, const auto & container, auto && condition) {
		return hpx::all_of(policy, container.begin(), container.end(), condition);
	};
} // namespace benchmark_all_of


