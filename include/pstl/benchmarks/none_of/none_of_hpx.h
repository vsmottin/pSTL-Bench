
#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_none_of
{

	const auto none_of_hpx = [](auto && policy, const auto & begin, const auto & end, auto && condition) {
		return hpx::none_of(policy, begin, end, condition);
	};

} // namespace benchmark_none_of


