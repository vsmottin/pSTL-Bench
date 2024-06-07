#pragma once

#include <functional>
#include <utility>

#include <hpx/algorithm.hpp>

#include "pstl/utils/elem_t.h"

namespace benchmark_transform_exclusive_scan
{
	const auto transform_exclusive_scan_hpx = [](auto && policy, auto & input, auto & output, auto && f) {
		return hpx::transform_exclusive_scan(policy, input.begin(), input.end(), output.begin(), pstl::elem_t{},
		                                     std::plus<>(), f);
	};
} // namespace benchmark_transform_exclusive_scan
