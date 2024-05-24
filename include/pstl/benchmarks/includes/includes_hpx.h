#pragma once

#include <hpx/numeric.hpp>

namespace benchmark_includes
{
	const auto includes_hpx = [](auto && policy, const auto & container, const auto & subset) {
		return hpx::includes(policy, container.begin(), container.end(), subset.begin(), subset.end());
	};
} // namespace benchmark_includes


