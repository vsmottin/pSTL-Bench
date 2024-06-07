#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_none_of
{
	const auto none_of_std = [](auto && policy, const auto & input, auto && condition) {
		return std::none_of(policy, input.begin(), input.end(), condition);
	};
} // namespace benchmark_none_of
