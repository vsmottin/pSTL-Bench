#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H

#include <parallel/numeric>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_gnu = [](auto && policy, const auto & container, auto & output) {
		__gnu_parallel::adjacent_difference(container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_adjacent_difference

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H
