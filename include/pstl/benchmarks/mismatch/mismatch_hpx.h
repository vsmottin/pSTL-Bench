#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_mismatch
{
	const auto mismatch_hpx = [](auto && policy, const auto & data1, const auto & data2) {
		return hpx::mismatch(data1.begin(), data1.end(), data2.begin());
	};
} // namespace benchmark_mismatch
