#pragma once

#include <algorithm>
#include <execution>

#include <benchmark/benchmark.h>

namespace benchmark_generate
{
	const auto generate_std = [](auto && policy, auto & container, auto && generator) {
		return std::generate(policy, container.begin(), container.end(), generator);
	};
} // namespace benchmark_generate


