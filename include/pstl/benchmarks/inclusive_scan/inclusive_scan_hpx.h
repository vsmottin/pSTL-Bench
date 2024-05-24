#pragma once

#include <hpx/numeric.hpp>

namespace benchmark_inclusive_scan
{
	const auto inclusive_scan_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::inclusive_scan(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_inclusive_scan


