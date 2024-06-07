#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_count
{
	const auto count_std = [](auto && policy, const auto & input, const auto & value) {
		return std::count(policy, input.begin(), input.end(), value);
	};
} // namespace benchmark_count
