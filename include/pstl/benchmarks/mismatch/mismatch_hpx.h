#ifndef PSTL_BENCH_MISMATCH_HPX_H
#define PSTL_BENCH_MISMATCH_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_mismatch
{
	const auto mismatch_hpx = [](auto && policy, const auto & data1, const auto & data2) {
		return hpx::mismatch(data1.begin(), data1.end(), data2.begin());
	};
} // namespace benchmark_mismatch

#endif //PSTL_BENCH_MISMATCH_HPX_H
