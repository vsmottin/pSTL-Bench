#pragma once

#include <algorithm>
#include <vector>

#include <parallel/algorithm>

namespace benchmark_find
{
	const auto find_gnu = [](auto && policy, const auto & input, const auto & find_val) {
		return __gnu_parallel::find(input.begin(), input.end(), find_val);
	};
} // namespace benchmark_find
