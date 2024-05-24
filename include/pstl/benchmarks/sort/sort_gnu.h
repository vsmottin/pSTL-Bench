#pragma once

#include <parallel/parallel.h>

namespace benchmark_sort
{
	const auto sort_gnu = []([[maybe_unused]] auto && policy, auto && begin, auto && end) {
		__gnu_parallel::sort(begin, end);
	};
} // namespace benchmark_sort


