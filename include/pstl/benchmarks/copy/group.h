#ifndef PSTL_BENCH_COPY_GROUP_H
#define PSTL_BENCH_COPY_GROUP_H

#include "benchmark_prefix.h"

#include "copy_utils.h"

#include "copy_std.h"

#ifdef USE_HPX
#include "copy_hpx.h"
#endif

//region copy_std
template<class Policy>
static void copy_std_wrapper(benchmark::State & state)
{
	benchmark_copy::benchmark_wrapper<Policy>(state, benchmark_copy::copy_std);
}

#define COPY_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(copy_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::copy"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                             \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define COPY_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::copy"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COPY_STD_WRAPPER
#endif
//endregion copy_std

//region copy_hpx
#ifdef USE_HPX
template<class Policy>
static void copy_hpx_wrapper(benchmark::State & state)
{
	benchmark_copy::benchmark_wrapper<Policy>(state, benchmark_copy::copy_hpx);
}

#define COPY_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::copy"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                        \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define COPY_HPX_WRAPPER
#endif

#define COPY_GROUP COPY_SEQ_WRAPPER COPY_STD_WRAPPER COPY_HPX_WRAPPER

#endif //PSTL_BENCH_COPY_GROUP_H
