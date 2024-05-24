#pragma once

#include <algorithm>

namespace benchmark_find
{
	const auto find_std = [](auto && policy, const auto & input, const auto & find_val) {
		return std::find(policy, input.begin(), input.end(), find_val);
	};
} // namespace benchmark_find
