#pragma once

#include <algorithm>

namespace benchmark_for_each
{

	const auto for_each_std = [](auto && policy, auto & input_data, auto && f) {
		std::for_each(policy, input_data.begin(), input_data.end(), f);
	};

} // namespace benchmark_for_each
