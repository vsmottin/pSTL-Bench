#pragma once

#include <algorithm>

#if defined(PSTL_BENCH_USE_TBB)
#include <tbb/parallel_sort.h>
#endif //USE_TBB

namespace benchmark_sort
{
	const auto sort_std = [](auto && policy, auto & input) {
#if defined(PSTL_BENCH_USE_TBB)
	// Show compiler message if TBB is used
#warning \
    "Using tbb::parallel_sort since std::sort(parallel_policy) explodes in memory usage. See: https://github.com/llvm/llvm-project/issues/78956#issue-2093630075"
		tbb::parallel_sort(input.begin(), input.end());
#else
		std::sort(policy, input.begin(), input.end());
#endif //USE_TBB
	};
} // namespace benchmark_sort
