
#ifndef PSTL_BENCH_B5_3_UNIQUE_COPY_H
#define PSTL_BENCH_B5_3_UNIQUE_COPY_H

#include <algorithm>
#include <benchmark_utils.h>
#include <cmath>
#include <vector>


namespace B5
{

	const auto b5_3_unique_copy_default = [](auto && policy, const auto & container, auto & result) {
		std::unique_copy(policy, container.begin(), container.end(), result.begin());
	};

}

#endif //PSTL_BENCH_B5_3_UNIQUE_COPY_H
