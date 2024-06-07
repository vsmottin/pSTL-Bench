#pragma once

#include <algorithm>
#include <execution>

namespace benchmark_any_of
{

	const auto any_of_std = [](auto && policy, const auto & input, auto && condition) {
		return std::any_of(policy, input.begin(), input.end(), condition);
	};

} // namespace benchmark_any_of
