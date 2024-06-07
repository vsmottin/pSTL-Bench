#pragma once

#include <parallel/algorithm>

namespace benchmark_search
{
	const auto search_gnu = []([[maybe_unused]] auto && policy, const auto & data1, const auto & data2) {
		return __gnu_parallel::search(data1.begin(), data1.end(), data2.begin(), data2.end());
	};
} // namespace benchmark_search
