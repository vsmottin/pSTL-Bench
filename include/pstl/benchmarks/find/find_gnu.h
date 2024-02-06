
#ifndef PSTL_BENCH_FIND_GNU_H
#define PSTL_BENCH_FIND_GNU_H

#include <algorithm>
#include <vector>

#include <parallel/algorithm>

namespace benchmark_find
{
	const auto find_gnu = [](auto && policy, const auto & container, const auto & find_val) {
		return __gnu_parallel::find(container.begin(), container.end(), find_val);
	};
} // namespace benchmark_find

#endif //PSTL_BENCH_FIND_GNU_H
