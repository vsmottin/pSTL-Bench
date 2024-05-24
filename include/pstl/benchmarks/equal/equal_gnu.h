#pragma once

#include <parallel/algorithm>

namespace benchmark_equal
{
	const auto equal_gnu = [](auto && policy, const auto & container, auto & output) {
		__gnu_parallel::equal(container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_equal


