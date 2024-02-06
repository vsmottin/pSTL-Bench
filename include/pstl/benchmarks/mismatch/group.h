#ifndef PSTL_BENCH_MISMATCH_GROUP_H
#define PSTL_BENCH_MISMATCH_GROUP_H

#include "benchmark_prefix.h"

#include "mismatch_utils.h"

#include "mismatch_std.h"

#ifdef USE_GNU
#include "mismatch_gnu.h"
#endif

#ifdef USE_HPX
#include "mismatch_hpx.h"
#endif

//region mismatch_std
template<class Policy>
static void mismatch_std_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_std);
}

#define MISMATCH_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(mismatch_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::mismatch"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define MISMATCH_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::mismatch"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MISMATCH_STD_WRAPPER
#endif
//endregion mismatch_std

//region mismatch_gnu
#ifdef USE_GNU
template<class Policy>
static void mismatch_gnu_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_gnu);
}

#define MISMATCH_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::mismatch"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MISMATCH_GNU_WRAPPER
#endif
//endregion mismatch_gnu

//region mismatch_hpx
#ifdef USE_HPX
template<class Policy>
static void mismatch_hpx_wrapper(benchmark::State & state)
{
	benchmark_mismatch::benchmark_wrapper<Policy>(state, benchmark_mismatch::mismatch_hpx);
}

#define MISMATCH_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(mismatch_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::mismatch"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define MISMATCH_HPX_WRAPPER
#endif

#define MISMATCH_GROUP   \
	MISMATCH_SEQ_WRAPPER \
	MISMATCH_STD_WRAPPER \
	MISMATCH_GNU_WRAPPER \
	MISMATCH_HPX_WRAPPER

#endif //PSTL_BENCH_MISMATCH_GROUP_H
