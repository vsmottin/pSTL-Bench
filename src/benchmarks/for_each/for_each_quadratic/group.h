#ifndef PSTL_BENCH_FOR_EACH_QUADRATIC_GROUP_H
#define PSTL_BENCH_FOR_EACH_QUADRATIC_GROUP_H

#include <benchmark/benchmark.h>

#include "../for_each_utils.h"

#include "for_each_std_quadratic.h"

#ifdef USE_OMP
#include "for_each_omp_quadratic.h"
#endif

#ifdef USE_GNU_PSTL
#include "for_each_gnu_quadratic.h"
#endif

//region for_each_quadratic
template<class OuterPolicy, class InnerPolicy>
static void for_each_std_quadratic_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_std_quadratic);
}

#define FOR_EACH_STD_QUADRATIC_WRAPPER                                                               \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 15, 1 << 15);                                                                   \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_std_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("std::for_each_quadratic_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);
//endregion for_each_quadratic

//region for_each_quadratic_omp
#ifdef USE_OMP
template<class OuterPolicy, class InnerPolicy>
static void for_each_omp_quadratic_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_omp_quadratic);
}

#define FOR_EACH_OMP_QUADRATIC_WRAPPER                                                               \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 15, 1 << 15);                                                                   \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_omp_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("omp::for_each_quadratic_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);
#else
#define FOR_EACH_OMP_QUADRATIC_WRAPPER
#endif
//endregion for_each_quadratic_omp

//region for_each_quadratic_gnu
#ifdef USE_GNU_PSTL
template<class OuterPolicy, class InnerPolicy>
static void for_each_gnu_quadratic_wrapper(benchmark::State & state)
{
	benchmark_for_each::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(
	    state, benchmark_for_each::for_each_gnu_quadratic);
}

#define FOR_EACH_GNU_QUADRATIC_WRAPPER                                                               \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 15, 1 << 15);                                                                   \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_wrapper, std::execution::sequenced_policy,            \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(for_each_gnu_quadratic_wrapper, std::execution::parallel_policy,             \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("gnu::for_each_quadratic_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);
#else
#define FOR_EACH_GNU_QUADRATIC_WRAPPER
#endif
//endregion for_each_quadratic_omp


#define FOR_EACH_QUADRATIC_GROUP   \
	FOR_EACH_STD_QUADRATIC_WRAPPER \
	FOR_EACH_OMP_QUADRATIC_WRAPPER \
	FOR_EACH_GNU_QUADRATIC_WRAPPER

#endif //PSTL_BENCH_FOR_EACH_QUADRATIC_GROUP_H
