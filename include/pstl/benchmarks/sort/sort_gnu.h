#pragma once

#include <parallel/parallel.h>

namespace benchmark_sort
{
	const auto sort_gnu = []([[maybe_unused]] auto && policy, auto & input) {
		__gnu_parallel::sort(input.begin(), input.end());
	};
} // namespace benchmark_sort
