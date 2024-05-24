#pragma once

#include <algorithm>

namespace benchmark_transform_inclusive_scan
{

	const auto transform_inclusive_scan_std = [](auto && policy, auto & input_data, auto & output, auto && f) {
		return std::transform_inclusive_scan(policy, input_data.begin(), input_data.end(), output.begin(),
		                                     std::plus<>(), f);
	};

} // namespace benchmark_transform_inclusive_scan


