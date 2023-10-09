#ifndef PSTL_BENCH_B1_3_GROUP_H
#define PSTL_BENCH_B1_3_GROUP_H

#include <benchmark/benchmark.h>

#include "../b1_utils.h"

#include "b1_3_for_each_quadratic.h"

#ifdef USE_OMP
#include "b1_3_for_each_quadratic_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b1_3_for_each_quadratic_gnu.h"
#endif

//region b1_3_for_each_quadratic
template<class OuterPolicy, class InnerPolicy>
static void b1_3_for_each_quadratic_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(state, B1::b1_3_for_each_quadratic);
}

#define B1_3_FOR_EACH_QUADRATIC_WRAPPER                                                              \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 15, 1 << 15);                                                                   \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_wrapper, std::execution::parallel_policy,            \
	                    std::execution::sequenced_policy)                                            \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);                                                                    \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_wrapper, std::execution::parallel_policy,            \
	                    std::execution::parallel_policy)                                             \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                      \
	    ->Range(1 << 5, 1 << 15);
//endregion b1_3_for_each_quadratic

//region b1_3_for_each_quadratic_omp
#ifdef USE_OMP
template<class OuterPolicy, class InnerPolicy>
static void b1_3_for_each_quadratic_omp_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(state, B1::b1_3_for_each_quadratic_omp);
}

#define B1_3_FOR_EACH_QUADRATIC_OMP_WRAPPER                                                              \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_omp_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                                \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_omp_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 15, 1 << 15);                                                                       \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_omp_wrapper, std::execution::parallel_policy,            \
	                    std::execution::sequenced_policy)                                                \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_omp_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);                                                                        \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_omp_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::parallel_policy)                                                 \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_omp_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);                                                                        \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_omp_wrapper, std::execution::parallel_policy,            \
	                    std::execution::parallel_policy)                                                 \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_omp_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);
#else
#define B1_3_FOR_EACH_QUADRATIC_OMP_WRAPPER
#endif
//endregion b1_3_for_each_quadratic_omp

//region b1_3_for_each_quadratic_gnu
#ifdef USE_GNU_PSTL
template<class OuterPolicy, class InnerPolicy>
static void b1_3_for_each_quadratic_gnu_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(state, B1::b1_3_for_each_quadratic_gnu);
}

#define B1_3_FOR_EACH_QUADRATIC_GNU_WRAPPER                                                              \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_gnu_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                                \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_gnu_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 15, 1 << 15);                                                                       \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_gnu_wrapper, std::execution::parallel_policy,            \
	                    std::execution::sequenced_policy)                                                \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_gnu_outer_std::execution::parallel_policy_seq"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);                                                                        \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_gnu_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::parallel_policy)                                                 \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_gnu_outer_std::execution::sequenced_policy_par")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);                                                                        \
	BENCHMARK_TEMPLATE2(b1_3_for_each_quadratic_gnu_wrapper, std::execution::parallel_policy,            \
	                    std::execution::parallel_policy)                                                 \
	    ->Name(BENCHMARK_NAME("b1_3_for_each_quadratic_gnu_outer_std::execution::parallel_policy_par"))  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                          \
	    ->Range(1 << 5, 1 << 15);
#else
#define B1_3_FOR_EACH_QUADRATIC_GNU_WRAPPER
#endif
//endregion b1_3_for_each_quadratic_omp


#define B1_3_FOR_EACH_QUADRATIC_GROUP   \
	B1_3_FOR_EACH_QUADRATIC_WRAPPER     \
	B1_3_FOR_EACH_QUADRATIC_OMP_WRAPPER \
	B1_3_FOR_EACH_QUADRATIC_GNU_WRAPPER

#endif //PSTL_BENCH_B1_3_GROUP_H
