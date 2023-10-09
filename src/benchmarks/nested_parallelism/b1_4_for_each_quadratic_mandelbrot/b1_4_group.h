#ifndef PSTL_BENCH_B1_4_GROUP_H
#define PSTL_BENCH_B1_4_GROUP_H

#include <benchmark/benchmark.h>

#include "../b1_utils.h"

#include "b1_4_for_each_quadratic_mandelbrot.h"

#ifdef USE_OMP
#include "b1_4_for_each_quadratic_mandelbrot_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b1_4_for_each_quadratic_mandelbrot_gnu.h"
#endif

//region b1_4_for_each_quadratic_mandelbrot
template<class OuterPolicy, class InnerPolicy>
static void b1_4_for_each_quadratic_mandelbrot_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, B1::b1_4_for_each_quadratic_mandelbrot);
}

#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer)                                                       \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                                       \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 13, 1 << 13);                                                                              \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_wrapper, outer, std::execution::parallel_policy)     \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                 \
	    ->Range(1 << 5, 1 << 13);
//endregion b1_4_for_each_quadratic_mandelbrot


//region b1_4_for_each_quadratic_mandelbrot_omp
#ifdef USE_OMP
template<class OuterPolicy, class InnerPolicy>
static void b1_4_for_each_quadratic_mandelbrot_omp_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, B1::b1_4_for_each_quadratic_mandelbrot_omp);
}

#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(outer)                                                       \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_omp_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                                           \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_omp_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                     \
	    ->Range(1 << 13, 1 << 13);                                                                                  \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_omp_wrapper, outer, std::execution::parallel_policy)     \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_omp_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                     \
	    ->Range(1 << 5, 1 << 13);
#else
#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(outer)
#endif
//endregion b1_4_for_each_quadratic_mandelbrot_omp

//region b1_4_for_each_quadratic_mandelbrot_gnu
#ifdef USE_GNU_PSTL
template<class OuterPolicy, class InnerPolicy>
static void b1_4_for_each_quadratic_mandelbrot_gnu_wrapper(benchmark::State & state)
{
	B1::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(
	    state, B1::b1_4_for_each_quadratic_mandelbrot_gnu);
}

#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_GNU_WRAPPER(outer)                                                       \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_gnu_wrapper, std::execution::sequenced_policy,           \
	                    std::execution::sequenced_policy)                                                           \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_gnu_outer_std::execution::sequenced_policy_seq")) \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                     \
	    ->Range(1 << 13, 1 << 13);                                                                                  \
	BENCHMARK_TEMPLATE2(b1_4_for_each_quadratic_mandelbrot_gnu_wrapper, outer, std::execution::parallel_policy)     \
	    ->Name(BENCHMARK_NAME("b1_4_for_each_quadratic_mandelbrot_gnu_outer_" xstr(outer) "_par"))                  \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                                                     \
	    ->Range(1 << 5, 1 << 13);
#else
#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_GNU_WRAPPER(outer)
#endif
//endregion b1_4_for_each_quadratic_mandelbrot_gnu


#define B1_4_FOR_EACH_QUADRATIC_MANDELBROT_GROUP(outer)   \
	B1_4_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer)     \
	B1_4_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(outer) \
	B1_4_FOR_EACH_QUADRATIC_MANDELBROT_GNU_WRAPPER(outer)

#endif //PSTL_BENCH_B1_4_GROUP_H
