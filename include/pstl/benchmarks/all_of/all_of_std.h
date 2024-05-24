#pragma once

#include <execution>
#include <numeric>

namespace benchmark_all_of
{
	const auto all_of_std = [](auto && policy, const auto & input, auto && condition) {
		return std::all_of(policy, input.begin(), input.end(), condition);
	};
} // namespace benchmark_all_of
