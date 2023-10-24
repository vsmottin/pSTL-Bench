#ifndef PSTL_BENCH_FOR_EACH_GROUP_H
#define PSTL_BENCH_FOR_EACH_GROUP_H

#include "benchmark_prefix.h"

#include <benchmark/benchmark.h>

#include "for_each_utils.h"

#include "for_each_std.h"

#ifdef USE_GNU_PSTL
#include "for_each_gnu.h"
#endif

//region for_each
template<class Policy>
static void for_each_std_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_std);
}

#define FOR_EACH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(for_each_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::for_each_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define FOR_EACH_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(for_each_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::for_each_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FOR_EACH_STD_WRAPPER
#endif
//endregion for_each

//region for_each_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void for_each_gnu_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_wrapper<Policy>(state, benchmark_for_each::for_each_gnu);
}

#define FOR_EACH_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(for_each_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::for_each_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define FOR_EACH_GNU_WRAPPER
#endif
//endregion for_each_gnu

#define FOR_EACH_GROUP   \
	FOR_EACH_SEQ_WRAPPER \
	FOR_EACH_STD_WRAPPER \
	FOR_EACH_GNU_WRAPPER

#endif //PSTL_BENCH_FOR_EACH_GROUP_H
