#pragma once

#include <algorithm>
#include <vector>

#include <cmath>

#include <benchmark/benchmark.h>

#include "pstl/utils/elem_t.h"

namespace benchmark_transform_reduce
{

	const auto transform_reduce_std = [](auto && policy, auto & input, auto && f) {
		return std::transform_reduce(policy, input.cbegin(), input.cend(), pstl::elem_t{}, std::plus<>(), f);
	};

} // namespace benchmark_transform_reduce


