#ifndef PSTL_BENCH_MAX_ELEMENT_GNU_H
#define PSTL_BENCH_MAX_ELEMENT_GNU_H

#include <parallel/algorithm>

namespace benchmark_max_element
{
	const auto max_element_gnu = [](auto && policy, const auto & input) {
		return __gnu_parallel::max_element(input.begin(), input.end());
	};
} // namespace benchmark_max_element

#endif //PSTL_BENCH_MAX_ELEMENT_GNU_H
