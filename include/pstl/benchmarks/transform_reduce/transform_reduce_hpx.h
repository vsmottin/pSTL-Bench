#pragma once

#include <functional>

#include <hpx/algorithm.hpp>

#include "pstl/utils/elem_t.h"

namespace benchmark_transform_reduce
{
	const auto transform_reduce_hpx = [](auto && policy, auto & input, auto && f) {
		return hpx::transform_reduce(policy, input.begin(), input.end(), pstl::elem_t{}, std::plus<>(), f);
	};
} // namespace benchmark_transform_reduce
