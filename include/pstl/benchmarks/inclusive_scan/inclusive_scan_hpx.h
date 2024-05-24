#pragma once

#include <hpx/numeric.hpp>

namespace benchmark_inclusive_scan
{
	const auto inclusive_scan_hpx = [](auto && policy, const auto & input, auto & output) {
		hpx::inclusive_scan(policy, input.begin(), input.end(), output.begin());
	};
} // namespace benchmark_inclusive_scan


