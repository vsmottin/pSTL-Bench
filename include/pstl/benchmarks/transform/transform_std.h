#pragma once

#include <algorithm>

namespace benchmark_transform
{

	const auto transform_std = [](auto && policy, auto & input, auto && f) {
		std::transform(policy, input.begin(), input.end(), input.begin(), f);
	};

} // namespace benchmark_transform


