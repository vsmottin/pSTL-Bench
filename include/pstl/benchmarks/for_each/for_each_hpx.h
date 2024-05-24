#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_for_each
{

	const auto for_each_hpx = [](auto && policy, auto & input_data, auto && f) {
		hpx::for_each(policy, input_data.begin(), input_data.end(), f);
	};

} // namespace benchmark_for_each


