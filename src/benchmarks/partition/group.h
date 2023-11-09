#ifndef PSTL_BENCH_PARTITION_GROUP_H
#define PSTL_BENCH_PARTITION_GROUP_H

#include "benchmark_prefix.h"

#include "partition_utils.h"

#include "partition_std.h"

#ifdef USE_GNU
#include "partition_gnu.h"
#endif

#ifdef USE_HPX
#include "partition_hpx.h"
#endif

//region partition_std
template<class Policy>
static void partition_std_wrapper(benchmark::State & state)
{
	benchmark_partition::benchmark_wrapper<Policy>(state, benchmark_partition::partition_std);
}

#define PARTITION_SEQ_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(partition_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME_WITH_BACKEND("SEQ", "std::partition"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                  \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);

#ifdef USE_PSTL
#define PARTITION_STD_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(partition_std_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("std::partition"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define PARTITION_STD_WRAPPER
#endif
//endregion partition_std

//region partition_gnu
#ifdef USE_GNU
template<class Policy>
static void partition_gnu_wrapper(benchmark::State & state)
{
	benchmark_partition::benchmark_wrapper<Policy>(state, benchmark_partition::partition_gnu);
}

#define PARTITION_GNU_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(partition_gnu_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::partition"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define PARTITION_GNU_WRAPPER
#endif
//endregion partition_gnu

#ifdef USE_HPX
template<class Policy>
static void partition_hpx_wrapper(benchmark::State & state)
{
	benchmark_partition::benchmark_wrapper<Policy>(state, benchmark_partition::partition_hpx);
}

#define PARTITION_HPX_WRAPPER                                                   \
	BENCHMARK_TEMPLATE1(partition_hpx_wrapper, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("hpx::partition"))                                \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                 \
	    ->Range(MIN_INPUT_SIZE, MAX_INPUT_SIZE);
#else
#define PARTITION_HPX_WRAPPER
#endif

#define PARTITION_GROUP   \
	PARTITION_SEQ_WRAPPER \
	PARTITION_STD_WRAPPER \
	PARTITION_GNU_WRAPPER \
	PARTITION_HPX_WRAPPER

#endif //PSTL_BENCH_PARTITION_GROUP_H
