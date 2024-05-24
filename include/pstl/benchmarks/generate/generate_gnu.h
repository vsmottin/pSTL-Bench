#pragma once

#include <parallel/algorithm>

namespace benchmark_generate
{
	const auto generate_gnu = []([[maybe_unused]] auto && policy, auto & container, auto && generator) {
		return __gnu_parallel::generate(container.begin(), container.end(), generator);
	};
} // namespace benchmark_generate


