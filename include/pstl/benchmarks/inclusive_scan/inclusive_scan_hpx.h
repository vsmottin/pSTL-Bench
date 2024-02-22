#ifndef PSTL_BENCH_INCLUSIVE_SCAN_HPX_H
#define PSTL_BENCH_INCLUSIVE_SCAN_HPX_H

#include <hpx/numeric.hpp>

namespace benchmark_inclusive_scan
{
	const auto inclusive_scan_hpx = [](auto && policy, const auto & container, auto & output) {
		hpx::inclusive_scan(policy, container.begin(), container.end(), output.begin());
	};
} // namespace benchmark_inclusive_scan

#endif //PSTL_BENCH_INCLUSIVE_SCAN_HPX_H
