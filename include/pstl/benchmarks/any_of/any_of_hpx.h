
#pragma once

#include "pstl/utils/utils.h"
#include <vector>

#include <hpx/algorithm.hpp>

namespace benchmark_any_of
{

	const auto any_of_hpx = [](auto && policy, const auto & container, auto && condition) {
		return hpx::any_of(policy, container.begin(), container.end(), condition);
	};

} // namespace benchmark_any_of


