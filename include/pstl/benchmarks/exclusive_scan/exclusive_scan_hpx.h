#ifndef PSTL_BENCH_EXCLUSIVE_SCAN_HPX_H
#define PSTL_BENCH_EXCLUSIVE_SCAN_HPX_H

#include <hpx/numeric.hpp>

namespace benchmark_exclusive_scan
{
	const auto exclusive_scan_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::exclusive_scan(policy, container.begin(), container.end(), output.begin(), 0);
	};
} // namespace benchmark_exclusive_scan

#endif //PSTL_BENCH_EXCLUSIVE_SCAN_HPX_H
