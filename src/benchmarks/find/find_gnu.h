
#ifndef PSTL_BENCH_FIND_GNU_H
#define PSTL_BENCH_FIND_GNU_H

#include <algorithm>
#include <vector>

#include <parallel/algorithm>

#include <benchmark_utils.h>

namespace benchmark_find
{

	const auto find_gnu = [](auto && policy, const auto & container, const auto & find_val) {
		return __gnu_parallel::find(container.begin(), container.end(), find_val);
	};

}

#endif //PSTL_BENCH_FIND_GNU_H
