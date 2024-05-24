#pragma once

#include <algorithm>

#if defined(USE_TBB)
#include <tbb/parallel_sort.h>
#endif //USE_TBB

namespace benchmark_sort
{
	const auto sort_std = [](auto && policy, auto && begin, auto && end) {
#if defined(USE_TBB)
	// Show compiler message if TBB is used
#warning \
    "Using tbb::parallel_sort since std::sort(parallel_policy) explodes in memory usage. See: https://github.com/llvm/llvm-project/issues/78956#issue-2093630075"
		tbb::parallel_sort(begin, end);
#else
		std::sort(policy, begin, end);
#endif //USE_TBB
	};
} // namespace benchmark_sort
