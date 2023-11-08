#ifndef PSTL_BENCH_ADJACENT_FIND_GNU_H
#define PSTL_BENCH_ADJACENT_FIND_GNU_H

#include <parallel/algorithm>

namespace benchmark_adjacent_find
{
	const auto adjacent_find_gnu = [](auto && policy, const auto & container, auto & output) {
		return __gnu_parallel::adjacent_find(container.begin(), container.end());
	};
} // namespace benchmark_adjacent_find

#endif //PSTL_BENCH_ADJACENT_FIND_GNU_H
