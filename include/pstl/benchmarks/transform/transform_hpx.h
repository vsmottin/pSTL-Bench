#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_transform
{

	const auto transform_hpx = [](auto && policy, auto & input, auto && f) {
		hpx::transform(policy, input.begin(), input.end(), input.begin(), f);
	};

} // namespace benchmark_transform


