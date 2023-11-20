#ifndef PSTL_BENCH_GENERATE_GROUP_H
#define PSTL_BENCH_GENERATE_GROUP_H

#include "benchmark_prefix.h"

#include "generate_utils.h"

#include "generate_std.h"

#ifdef USE_GNU
#include "generate_gnu.h"
#endif

#ifdef USE_HPX
#include "generate_hpx.h"
#endif

//region generate_std
template<class Policy>
static void generate_std_wrapper(benchmark::State & state)
{
	benchmark_generate::benchmark_wrapper<Policy>(state, benchmark_generate::generate_std);
}

#define GENERATE_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(generate_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::generate"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define GENERATE_STD_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(generate_std_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::generate"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define GENERATE_STD_WRAPPER
#endif
//endregion generate_std

//region generate_gnu
#ifdef USE_GNU
template<class Policy>
static void generate_gnu_wrapper(benchmark::State & state)
{
	benchmark_generate::benchmark_wrapper<Policy>(state, benchmark_generate::generate_gnu);
}

#define GENERATE_GNU_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(generate_gnu_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::generate"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define GENERATE_GNU_WRAPPER
#endif
//endregion generate_gnu


#ifdef USE_HPX
template<class Policy>
static void generate_hpx_wrapper(benchmark::State & state)
{
	benchmark_generate::benchmark_wrapper<Policy>(state, benchmark_generate::generate_hpx);
}

#define GENERATE_HPX_WRAPPER                                                               \
	BENCHMARK_TEMPLATE1(generate_hpx_wrapper, std::execution::parallel_unsequenced_policy) \
	    ->Name(BENCHMARK_NAME("hpx::generate"))                                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define GENERATE_HPX_WRAPPER
#endif

#define GENERATE_GROUP   \
	GENERATE_SEQ_WRAPPER \
	GENERATE_STD_WRAPPER \
	GENERATE_GNU_WRAPPER \
	GENERATE_HPX_WRAPPER

#endif //PSTL_BENCH_GENERATE_GROUP_H
