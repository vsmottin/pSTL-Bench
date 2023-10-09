
#ifndef PSTL_BENCH_B5_2_PARTITION_H
#define PSTL_BENCH_B5_2_PARTITION_H

#include <algorithm>
#include <benchmark_utils.h>
#include <cmath>
#include <vector>

namespace B5
{

	const auto b5_2_partition = [](auto && policy, auto & container) {
		return std::partition(policy, container.begin(), container.end(), [](const auto & a) {
			const auto b = a + 2;
			const auto c = M_PI;

			const auto a_squared = std::pow(a, 2);
			const auto b_squared = std::pow(b, 2);
			const auto c_squared = std::pow(c, 2);

			return a_squared == ((int) b_squared + c_squared - 2 * b * c * std::cos(a));
		});
	};

}

#endif //PSTL_BENCH_B5_2_PARTITION_H
