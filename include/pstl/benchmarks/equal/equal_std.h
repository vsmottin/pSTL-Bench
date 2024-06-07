#pragma once

#include <execution>
#include <numeric>

namespace benchmark_equal
{
	const auto equal_std = [](auto && policy, const auto & input, auto & output) {
		std::equal(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_equal
