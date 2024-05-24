#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_reduce
{
	const auto reduce_hpx = [](auto && policy, const auto & begin, const auto & end) {
		return hpx::reduce(policy, begin, end, pstl::elem_t{});
	};
} // namespace benchmark_reduce


