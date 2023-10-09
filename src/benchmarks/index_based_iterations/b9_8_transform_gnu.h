
#ifndef PSTL_BENCH_B9_8_TRANSFORM_GNU_H
#define PSTL_BENCH_B9_8_TRANSFORM_GNU_H

#include <vector>

#include <parallel/algorithm>

namespace B9
{

	const auto b9_8_transform_gnu = [](auto && policy, const auto & input_data, auto & res, auto && f) {
		__gnu_parallel::transform(std::begin(input_data), std::end(input_data), std::begin(res), f);
	};

}

#endif //PSTL_BENCH_B9_8_TRANSFORM_GNU_H
