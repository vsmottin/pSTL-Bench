#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_set_difference
{
	const auto set_difference_hpx = [](auto && policy, const auto & first1, const auto & last1, const auto & first2,
	                                   const auto & last2, auto d_first) {
		return hpx::set_difference(policy, first1, last1, first2, last2, d_first);
	};
} // namespace benchmark_set_difference


