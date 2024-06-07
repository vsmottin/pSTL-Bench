#pragma once

#include <hpx/numeric.hpp>

namespace benchmark_includes
{
	const auto includes_hpx = [](auto && policy, const auto & input, const auto & subset) {
		return hpx::includes(policy, input.begin(), input.end(), subset.begin(), subset.end());
	};
} // namespace benchmark_includes
