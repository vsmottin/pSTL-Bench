#pragma once

#include <parallel/algorithm>

namespace benchmark_mismatch
{
	const auto mismatch_gnu = []([[maybe_unused]] auto && policy, const auto & data1, const auto & data2) {
		return __gnu_parallel::mismatch(data1.begin(), data1.end(), data2.begin());
	};
} // namespace benchmark_mismatch
