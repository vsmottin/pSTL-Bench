#ifndef PSTL_BENCH_FOR_EACH_HPX_H
#define PSTL_BENCH_FOR_EACH_HPX_H

#include <hpx/algorithm.hpp>

namespace benchmark_for_each
{

	const auto for_each_hpx = [](auto && policy, auto & input_data, auto && f) {
		hpx::for_each(policy, input_data.begin(), input_data.end(), f);
	};

} // namespace benchmark_for_each

#endif //PSTL_BENCH_FOR_EACH_HPX_H
