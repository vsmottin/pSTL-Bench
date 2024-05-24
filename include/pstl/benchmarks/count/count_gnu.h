#pragma once

#include <parallel/algorithm>

namespace benchmark_count
{
	const auto count_gnu = [](auto && policy, const auto & input, const auto & value) {
		return __gnu_parallel::count(input.begin(), input.end(), value);
	};
} // namespace benchmark_count
