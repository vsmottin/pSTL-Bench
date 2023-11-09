#ifndef PSTL_BENCH_MIN_ELEMENT_GNU_H
#define PSTL_BENCH_MIN_ELEMENT_GNU_H

#include <parallel/algorithm>

namespace benchmark_min_element
{
	const auto min_element_gnu = [](auto && policy, const auto & input) {
		return __gnu_parallel::min_element(input.begin(), input.end());
	};
} // namespace benchmark_min_element

#endif //PSTL_BENCH_MIN_ELEMENT_GNU_H
