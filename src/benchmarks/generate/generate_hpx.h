#ifndef PSTL_BENCH_GENERATE_HPX_H
#define PSTL_BENCH_GENERATE_HPX_H

#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>

#include <benchmark/benchmark.h>

namespace benchmark_generate
{
	const auto generate_hpx = [](auto && policy, auto & container, auto && generator) {
		return hpx::generate(policy, container.begin(), container.end(), generator);
	};
}

#endif //PSTL_BENCH_GENERATE_HPX_H
