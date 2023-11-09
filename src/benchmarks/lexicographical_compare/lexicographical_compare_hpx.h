#ifndef PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_HPX_H
#define PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_lexicographical_compare
{
	const auto lexicographical_compare_hpx = [](auto && policy, const auto & data_a, const auto & data_b) {
		return hpx::lexicographical_compare(policy, data_a.begin(), data_a.end(), data_b.begin(), data_b.end());
	};
}

#endif //PSTL_BENCH_LEXICOGRAPHICAL_COMPARE_HPX_H
