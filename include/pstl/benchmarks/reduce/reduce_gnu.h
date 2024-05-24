#pragma once

#include "pstl/utils/elem_t.h"

#include <parallel/numeric>

namespace benchmark_reduce
{
	const auto reduce_gnu = []([[maybe_unused]] auto && policy, const auto & input) {
		return __gnu_parallel::accumulate(input.begin(), input.end(), pstl::elem_t{});
	};
} // namespace benchmark_reduce
