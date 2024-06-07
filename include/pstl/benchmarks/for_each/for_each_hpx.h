#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_for_each
{

	const auto for_each_hpx = [](auto && policy, auto & input, auto && f) {
		hpx::for_each(policy, input.begin(), input.end(), f);
	};

} // namespace benchmark_for_each
