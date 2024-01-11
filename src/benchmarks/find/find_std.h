
#ifndef PSTL_BENCH_FIND_STD_H
#define PSTL_BENCH_FIND_STD_H

#include <algorithm>

namespace benchmark_find
{
	const auto find_std = [](auto && policy, const auto & container, const auto & find_val) {
		return std::find(policy, container.begin(), container.end(), find_val);
	};
} // namespace benchmark_find

#endif //PSTL_BENCH_FIND_STD_H
