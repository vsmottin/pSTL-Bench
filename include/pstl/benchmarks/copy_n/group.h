#pragma once

#include "pstl/utils/benchmark_naming.h"

#include "copy_n_utils.h"

#include "copy_n_std.h"

#ifdef USE_HPX
#include "copy_n_hpx.h"
#endif

//region copy_n_std
template<class Policy>
static void copy_n_std_wrapper(benchmark::State & state)
{
	benchmark_copy_n::benchmark_wrapper<Policy>(state, benchmark_copy_n::copy_n_std);
}

#define COPY_N_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(copy_n_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::copy_n"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                               \
	    ->UseManualTime();

#ifdef USE_PSTL
#define COPY_N_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_n_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::copy_n"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                          \
	    ->UseManualTime();
#else
#define COPY_N_STD_WRAPPER
#endif
//endregion copy_n_std

//region copy_n_hpx
#ifdef USE_HPX
template<class Policy>
static void copy_n_hpx_wrapper(benchmark::State & state)
{
	benchmark_copy_n::benchmark_wrapper<Policy>(state, benchmark_copy_n::copy_n_hpx);
}

#define COPY_N_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(copy_n_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::copy_n"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE)                                          \
	    ->UseManualTime();
#else
#define COPY_N_HPX_WRAPPER
#endif

#define COPY_N_GROUP COPY_N_SEQ_WRAPPER COPY_N_STD_WRAPPER COPY_N_HPX_WRAPPER


