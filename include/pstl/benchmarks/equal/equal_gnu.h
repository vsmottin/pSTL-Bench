#pragma once

#include <parallel/algorithm>

namespace benchmark_equal
{
	const auto equal_gnu = [](auto && policy, const auto & input, auto & output) {
		__gnu_parallel::equal(input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_equal
