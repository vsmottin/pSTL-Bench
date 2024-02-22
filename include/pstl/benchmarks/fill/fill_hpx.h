#ifndef PSTL_BENCH_FILL_HPX_H
#define PSTL_BENCH_FILL_HPX_H

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_fill
{
	const auto fill_hpx = [](auto && policy, auto & container, const auto & value) {
		return hpx::fill(policy, container.begin(), container.end(), value);
	};
} // namespace benchmark_fill

#endif //PSTL_BENCH_FILL_HPX_H
