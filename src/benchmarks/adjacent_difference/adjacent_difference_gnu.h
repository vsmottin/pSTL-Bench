#ifndef PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H
#define PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H

#include <parallel/numeric>

namespace benchmark_adjacent_difference
{
	const auto adjacent_difference_gnu = []([[maybe_unused]] auto && policy, const auto & input, auto & output) {
		__gnu_parallel::adjacent_difference(input.begin(), input.end(), output.begin(), std::minus<>());
	};
} // namespace benchmark_adjacent_difference

#endif //PSTL_BENCH_ADJACENT_DIFFERENCE_GNU_H
