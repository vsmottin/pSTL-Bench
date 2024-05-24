#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_is_sorted
{
	const auto is_sorted_hpx = [](auto && policy, const auto & begin, const auto & end) {
		return hpx::is_sorted(policy, begin, end);
	};
} // namespace benchmark_is_sorted


