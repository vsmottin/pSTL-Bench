
#ifndef PSTL_BENCH_B5_4_MINMAX_ELEMENT_H
#define PSTL_BENCH_B5_4_MINMAX_ELEMENT_H

#include <algorithm>
#include <vector>
#include <utility>
#include <benchmark_utils.h>

namespace B5 {

	const auto b5_4_minmax_element = [] (auto && policy, const auto & container) {
		return std::minmax_element(policy, container.begin(), container.end());
	};

}

#endif //PSTL_BENCH_B5_4_MINMAX_ELEMENT_H
