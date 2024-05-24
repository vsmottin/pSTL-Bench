#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_fill
{
	const auto fill_std = [](auto && policy, auto & input, const auto & value) {
		return std::fill(policy, input.begin(), input.end(), value);
	};
} // namespace benchmark_fill
