#ifndef PSTL_BENCH_GROUP_H
#define PSTL_BENCH_GROUP_H

#include "reduce_utils.h"

#include "reduce_std.h"

#ifdef USE_OMP
#include "reduce_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "reduce_gnu.h"
#endif

//region reduce_std
template<class Policy>
static void reduce_std_wrapper(benchmark::State & state)
{
	benchmark_reduce::benchmark_wrapper<Policy>(state, benchmark_reduce::reduce_std);
}

#define REDUCE_STD_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(reduce_std_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::reduce_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                              \
	BENCHMARK_TEMPLATE1(reduce_std_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("std::reduce_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion reduce_std

//region reduce_omp
#ifdef USE_OMP
template<class Policy>
static void reduce_omp_wrapper(benchmark::State & state)
{
	benchmark_reduce::benchmark_wrapper<Policy>(state, benchmark_reduce::reduce_omp);
}

#define REDUCE_OMP_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(reduce_omp_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("omp::reduce_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                              \
	BENCHMARK_TEMPLATE1(reduce_omp_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("omp::reduce_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define REDUCE_OMP_WRAPPER
#endif
//endregion reduce_omp

//region reduce_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void reduce_gnu_wrapper(benchmark::State & state)
{
	benchmark_reduce::benchmark_wrapper<Policy>(state, benchmark_reduce::reduce_gnu);
}

#define REDUCE_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(reduce_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("gnu::reduce_seq"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                              \
	BENCHMARK_TEMPLATE1(reduce_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("gnu::reduce_par"))                             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                               \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define REDUCE_GNU_WRAPPER
#endif


#define REDUCE_GROUP   \
	REDUCE_STD_WRAPPER \
	REDUCE_OMP_WRAPPER \
	REDUCE_GNU_WRAPPER

#endif //PSTL_BENCH_GROUP_H
