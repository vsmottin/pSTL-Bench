#ifndef PSTL_BENCH_GENERATE_GNU_H
#define PSTL_BENCH_GENERATE_GNU_H

#include <parallel/algorithm>

namespace benchmark_generate
{
	const auto generate_gnu = []([[maybe_unused]] auto && policy, auto & container, auto && generator) {
		return __gnu_parallel::generate(container.begin(), container.end(), generator);
	};
} // namespace benchmark_generate

#endif //PSTL_BENCH_GENERATE_GNU_H
