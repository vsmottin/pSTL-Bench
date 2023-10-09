
#ifndef PSTL_BENCH_B9_2_TRANSFORM_OLD_IOTA_H
#define PSTL_BENCH_B9_2_TRANSFORM_OLD_IOTA_H

#include <algorithm>
#include <benchmark_utils.h>
#include <numeric>
#include <vector>

namespace B9
{

	const auto b9_2_transform_old_iota = [](auto && policy, const auto & input_data, auto & res, auto && f) {
		std::vector<std::size_t> view(input_data.size());
		std::iota(view.begin(), view.end(), 0); // sadly this cannot be done with parallel stl
		std::transform(policy, view.begin(), view.end(), res.begin(),
		               [&input_data, &f](const auto & i) { return f(input_data[i]); });
	};

}

#endif //PSTL_BENCH_B9_2_TRANSFORM_OLD_IOTA_H
