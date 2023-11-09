#ifndef PSTL_BENCH_EQUAL_GNU_H
#define PSTL_BENCH_EQUAL_GNU_H

#include <parallel/algorithm>

namespace benchmark_equal
{
	const auto equal_gnu = [](auto && policy, const auto & container, auto & output) {
		__gnu_parallel::equal(container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_equal

#endif //PSTL_BENCH_EQUAL_GNU_H
