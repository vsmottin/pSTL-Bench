#ifndef PSTL_BENCH_REDUCE_GROUP_H
#define PSTL_BENCH_REDUCE_GROUP_H

#include "benchmark_prefix.h"

#include "reduce_utils.h"

#include "reduce_std.h"

#ifdef USE_GNU_PSTL
#include "reduce_gnu.h"
#endif

//region reduce_std
template<class Policy>
static void reduce_std_wrapper(benchmark::State & state)
{
	benchmark_reduce::benchmark_wrapper<Policy>(state, benchmark_reduce::reduce_std);
}

#define REDUCE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(reduce_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::reduce_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define REDUCE_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(reduce_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::reduce_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define REDUCE_STD_WRAPPER
#endif
//endregion reduce_std

//region reduce_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void reduce_gnu_wrapper(benchmark::State & state)
{
	benchmark_reduce::benchmark_wrapper<Policy>(state, benchmark_reduce::reduce_gnu);
}

#define REDUCE_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(reduce_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::reduce_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                              \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define REDUCE_GNU_WRAPPER
#endif
//endregion reduce_gnu

#define REDUCE_GROUP   \
	REDUCE_SEQ_WRAPPER \
	REDUCE_STD_WRAPPER \
	REDUCE_GNU_WRAPPER

#endif //PSTL_BENCH_REDUCE_GROUP_H
