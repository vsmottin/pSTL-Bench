
#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_none_of
{

	const auto none_of_hpx = [](auto && policy, const auto & input, auto && condition) {
		return hpx::none_of(policy, input.begin(), input.end(), condition);
	};

} // namespace benchmark_none_of
