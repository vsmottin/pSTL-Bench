#pragma once

#include <parallel/algorithm>

namespace benchmark_generate
{
	const auto generate_gnu = []([[maybe_unused]] auto && policy, auto & input, auto && generator) {
		return __gnu_parallel::generate(input.begin(), input.end(), generator);
	};
} // namespace benchmark_generate
