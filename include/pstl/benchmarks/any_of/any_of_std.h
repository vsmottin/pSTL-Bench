
#pragma once

#include "pstl/utils/utils.h"
#include <algorithm>
#include <vector>

namespace benchmark_any_of
{

	const auto any_of_std = [](auto && policy, const auto & container, auto && condition) {
		return std::any_of(policy, container.begin(), container.end(), condition);
	};

} // namespace benchmark_any_of


