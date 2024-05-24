
#pragma once

#include <algorithm>
#include <vector>

#include <parallel/algorithm>

namespace benchmark_find
{
	const auto find_gnu = [](auto && policy, const auto & container, const auto & find_val) {
		return __gnu_parallel::find(container.begin(), container.end(), find_val);
	};
} // namespace benchmark_find


