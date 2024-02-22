#ifndef PSTL_BENCH_COPY_IF_GROUP_H
#define PSTL_BENCH_COPY_IF_GROUP_H

#include "benchmark_prefix.h"

#include "copy_if_utils.h"

#include "copy_if_std.h"

#ifdef USE_HPX
#include "copy_if_hpx.h"
#endif

//region copy_if_std
template<class Policy>
static void copy_if_std_wrapper(benchmark::State & state)
{
	benchmark_copy_if::benchmark_wrapper<Policy>(state, benchmark_copy_if::copy_if_std);
}

#define COPY_IF_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(copy_if_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::copy_if"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                \
	    ->UseManualTime();

#ifdef USE_PSTL
#define COPY_IF_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_if_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::copy_if"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                           \
	    ->UseManualTime();
#else
#define COPY_IF_STD_WRAPPER
#endif
//endregion copy_if_std

//region copy_if_hpx
#ifdef USE_HPX
template<class Policy>
static void copy_if_hpx_wrapper(benchmark::State & state)
{
	benchmark_copy_if::benchmark_wrapper<Policy>(state, benchmark_copy_if::copy_if_hpx);
}

#define COPY_IF_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_if_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::copy_if"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                           \
	    ->UseManualTime();
#else
#define COPY_IF_HPX_WRAPPER
#endif

#define COPY_IF_GROUP COPY_IF_SEQ_WRAPPER COPY_IF_STD_WRAPPER COPY_IF_HPX_WRAPPER

#endif //PSTL_BENCH_COPY_IF_GROUP_H
