#pragma once

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

namespace benchmark_generate
{
	const auto generate_hpx = [](auto && policy, auto & input, auto && generator) {
		return hpx::generate(policy, input.begin(), input.end(), generator);
	};
} // namespace benchmark_generate
