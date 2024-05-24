#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_inplace_merge
{
	const auto inplace_merge_hpx = [](auto && policy, auto begin, auto middle, auto end) {
		return hpx::inplace_merge(policy, begin, middle, end);
	};
} // namespace benchmark_inplace_merge


