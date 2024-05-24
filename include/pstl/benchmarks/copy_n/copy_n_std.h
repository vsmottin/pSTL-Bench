#pragma once

#include <execution>
#include <numeric>

#include <benchmark/benchmark.h>

namespace benchmark_copy_n
{
	const auto copy_n_std = [](auto && policy, const auto & container, const auto & n, auto & output) {
		std::copy_n(policy, container.begin(), n, output.begin());
	};
} // namespace benchmark_copy_n


