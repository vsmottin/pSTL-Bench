#ifndef PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_INCLUSIVE_SCAN_HPX_H
#define PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_transform_inclusive_scan
{

	const auto transform_inclusive_scan_hpx = [](auto && policy, auto & input_data, auto & output, auto && f) {
		return hpx::transform_inclusive_scan(policy, input_data.begin(), input_data.end(), output.begin(),
		                                     std::plus<>(), f);
	};

} // namespace benchmark_transform_inclusive_scan

#endif //PSTL_BENCH_TRANSFORM_INCLUSIVE_SCAN_HPX_H
