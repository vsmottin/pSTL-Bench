
#ifndef PSTL_BENCH_B9_3_TRANSFORM_VIEWS_IOTA_H
#define PSTL_BENCH_B9_3_TRANSFORM_VIEWS_IOTA_H

#include <vector>
#include <algorithm>
#include <ranges>
#include <benchmark_utils.h>

namespace B9 {

	const auto b9_3_transform_views_iota = [] (auto && policy, const auto & input_data, auto & res, auto && f) {
		const auto &view = std::views::iota(0, static_cast<int>(input_data.size()));
		std::transform(policy, view.begin(), view.end(), res.begin(),
					   [&input_data, &f] (const auto & i) { return f(input_data[i]); });
	};

}

#endif //PSTL_BENCH_B9_3_TRANSFORM_VIEWS_IOTA_H
