
#ifndef PSTL_BENCH_B5_3_UNIQUE_COPY_GNU_H
#define PSTL_BENCH_B5_3_UNIQUE_COPY_GNU_H

#include <algorithm>
#include <cmath>
#include <vector>

#include <parallel/algorithm>

#include <benchmark_utils.h>


namespace B5
{

	const auto b5_3_unique_copy_gnu = [](auto && policy, const auto & container, auto & result) {
		__gnu_parallel::unique_copy(container.begin(), container.end(), result.begin());
	};

}

#endif //PSTL_BENCH_B5_3_UNIQUE_COPY_GNU_H
