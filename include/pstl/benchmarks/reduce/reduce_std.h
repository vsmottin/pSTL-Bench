#pragma once

#include "pstl/utils/elem_t.h"

#include <algorithm>
#include <execution>

namespace benchmark_reduce
{
	const auto reduce_std = [](auto && policy, const auto & input) {
		return std::reduce(policy, input.begin(), input.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce
