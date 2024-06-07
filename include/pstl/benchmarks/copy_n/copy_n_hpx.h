#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy_n
{
	const auto copy_n_hpx = [](auto && policy, const auto & input, const auto & n, auto & output) {
		hpx::copy_n(policy, input.begin(), n, output.begin());
	};
} // namespace benchmark_copy_n
