
#ifndef PSTL_BENCH_NONE_OF_STD_H
#define PSTL_BENCH_NONE_OF_STD_H

#include "pstl/utils.h"
#include <algorithm>
#include <vector>

namespace benchmark_none_of
{

	const auto none_of_std = [](auto && policy, const auto & container, auto && condition) {
		return std::none_of(policy, container.begin(), container.end(), condition);
	};

} // namespace benchmark_none_of

#endif //PSTL_BENCH_NONE_OF_STD_H
