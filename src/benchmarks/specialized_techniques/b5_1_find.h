
#ifndef PSTL_BENCH_B5_1_FIND_H
#define PSTL_BENCH_B5_1_FIND_H

#include <algorithm>
#include <benchmark_utils.h>
#include <vector>

namespace B5
{

	const auto b5_1_find = [](auto && policy, const auto & container, const auto & find_val) {
		return std::find(policy, container.begin(), container.end(), find_val);
	};

}

#endif //PSTL_BENCH_B5_1_FIND_H
