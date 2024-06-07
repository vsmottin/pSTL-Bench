#pragma once

#include <algorithm>
#include <execution>


namespace benchmark_generate
{
	const auto generate_std = [](auto && policy, auto & input, auto && generator) {
		return std::generate(policy, input.begin(), input.end(), generator);
	};
} // namespace benchmark_generate
