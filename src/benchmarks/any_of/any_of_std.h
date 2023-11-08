
#ifndef PSTL_BENCH_ANY_OF_STD_H
#define PSTL_BENCH_ANY_OF_STD_H

#include <algorithm>
#include <benchmark_utils.h>
#include <vector>

namespace benchmark_any_of
{

	const auto any_of_std = [](auto && policy, const auto & container, auto && condition) {
		return std::any_of(policy, container.begin(), container.end(), condition);
	};

}

#endif //PSTL_BENCH_ANY_OF_STD_H
