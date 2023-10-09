
#ifndef PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H
#define PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H

#include <benchmark_utils.h>
#include <numeric>
#include <utility>
#include <vector>

namespace B6
{

	const auto b6_1_inclusive_scan = [](auto && policy, const auto & container, auto & result) {
		std::inclusive_scan(policy, container.begin(), container.end(), result.begin());
	};

}

#endif //PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H
