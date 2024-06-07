#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_any_of
{

	const auto any_of_hpx = [](auto && policy, const auto & input, auto && condition) {
		return hpx::any_of(policy, input.begin(), input.end(), condition);
	};

} // namespace benchmark_any_of
