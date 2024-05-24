#pragma once

#include "pstl/utils/elem_t.h"

#include <hpx/algorithm.hpp>

namespace benchmark_reduce
{
	const auto reduce_hpx = [](auto && policy, const auto & input) {
		return hpx::reduce(policy, input.begin(), input.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce


