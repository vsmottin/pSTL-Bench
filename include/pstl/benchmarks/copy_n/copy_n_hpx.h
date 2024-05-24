#pragma once

#include <hpx/algorithm.hpp>

namespace benchmark_copy_n
{
	const auto copy_n_hpx = [](auto && policy, const auto & container, const auto & n, auto & output) {
		hpx::copy_n(policy, container.begin(), n, output.begin());
	};
} // namespace benchmark_copy_n


