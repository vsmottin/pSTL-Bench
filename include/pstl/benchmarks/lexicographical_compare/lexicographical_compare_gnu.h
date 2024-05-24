#pragma once

#include <parallel/algorithm>

namespace benchmark_lexicographical_compare
{
	const auto lexicographical_compare_gnu = []([[maybe_unused]] auto && policy, const auto & data_a,
	                                            const auto & data_b) {
		return __gnu_parallel::lexicographical_compare(data_a.begin(), data_a.end(), data_b.begin(), data_b.end());
	};
} // namespace benchmark_lexicographical_compare
