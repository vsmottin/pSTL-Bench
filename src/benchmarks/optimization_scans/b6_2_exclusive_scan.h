
#ifndef PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_H
#define PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_H

#include <numeric>
#include <vector>
#include <utility>
#include <benchmark_utils.h>

namespace B6 {

	const auto b6_2_exclusive_scan = [] (auto && policy,
										 const auto & container,
										 auto & result) {
		std::exclusive_scan(policy, container.begin(), container.end(), result.begin(), 0);
	};

}

#endif //PSTL_BENCH_B6_2_EXCLUSIVE_SCAN_H
