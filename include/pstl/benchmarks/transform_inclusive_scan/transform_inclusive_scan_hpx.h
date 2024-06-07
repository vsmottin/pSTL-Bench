#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_transform_inclusive_scan
{

	const auto transform_inclusive_scan_hpx = [](auto && policy, auto & input, auto & output, auto && f) {
		return hpx::transform_inclusive_scan(policy, input.begin(), input.end(), output.begin(), std::plus<>(), f);
	};

} // namespace benchmark_transform_inclusive_scan
