
#ifndef PSTL_BENCH_B5_1_FIND_GNU_H
#define PSTL_BENCH_B5_1_FIND_GNU_H

#include <algorithm>
#include <vector>

#include <parallel/algorithm>

#include <benchmark_utils.h>

namespace B5 {

	const auto b5_1_find_gnu = [] (auto && policy, const auto & container, const auto & find_val) {
		return __gnu_parallel::find(container.begin(), container.end(), find_val);
	};

}

#endif //PSTL_BENCH_B5_1_FIND_GNU_H
