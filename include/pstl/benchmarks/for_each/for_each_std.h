#pragma once

#include <algorithm>

namespace benchmark_for_each
{

	const auto for_each_std = [](auto && policy, auto & input, auto && f) {
		std::for_each(policy, input.begin(), input.end(), f);
	};

} // namespace benchmark_for_each
