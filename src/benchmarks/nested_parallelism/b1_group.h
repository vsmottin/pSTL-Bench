#ifndef PSTL_BENCH_B1_GROUP_H
#define PSTL_BENCH_B1_GROUP_H

#include <chrono>
#include <execution>
#include <ranges>
#include <benchmark/benchmark.h>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include "b1_1_for_each_linear.h"
#include "b1_2_for_each_quadratic.h"
#include "b1_4_for_each_exponential.h"
#include "b1_1_for_each_linear_mandelbrot.h"
#include "b1_2_for_each_quadratic_mandelbrot.h"

#include "b1_1_for_each_linear_omp.h"
#include "b1_1_for_each_linear_mandelbrot_omp.h"
#include "b1_2_for_each_quadratic_omp.h"
#include "b1_2_for_each_quadratic_mandelbrot_omp.h"
#include "b1_4_for_each_exponential_omp.h"

#include "b1_utils.h"

//region b1_1_for_each_linear
template<class Policy>
static void b1_1_for_each_linear_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_linear_wrapper<Policy>(state, B1::b1_1_for_each_linear);
}

#define B1_1_FOR_EACH_LINEAR_WRAPPER \
        BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, MAX_INPUT_SIZE);
//endregion b1_1_for_each_linear

//region b1_1_for_each_linear_omp
#ifdef USE_OMP

template<class Policy>
static void b1_1_for_each_linear_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_linear_wrapper<Policy>(state, B1::b1_1_for_each_linear_omp);
}

#define B1_1_FOR_EACH_LINEAR_OMP_WRAPPER
BENCHMARK_TEMPLATE1(b1_1_for_each_linear_omp_wrapper, std::execution::sequenced_policy)->Name(
		BENCHMARK_NAME("b1_1_for_each_linear_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE,
																									  MAX_INPUT_SIZE);
\

BENCHMARK_TEMPLATE1(b1_1_for_each_linear_omp_wrapper, std::execution::parallel_policy)->Name(
		BENCHMARK_NAME("b1_1_for_each_linear_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5,
																									  MAX_INPUT_SIZE);
#else
#define B1_1_FOR_EACH_LINEAR_OMP_WRAPPER
#endif
//endregion b1_1_for_each_linear_omp

//region b1_1_for_each_linear_mandelbrot
template<class Policy>
static void b1_1_for_each_linear_mandelbrot_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(state, B1::b1_1_for_each_linear_mandelbrot);
}

#define B1_1_FOR_EACH_LINEAR_MANDELBROT_WRAPPER \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, MAX_INPUT_SIZE);
//endregion b1_1_for_each_linear_mandelbrot

//region b1_1_for_each_linear_mandelbrot_omp
#ifdef USE_OMP

template<class Policy>
static void b1_1_for_each_linear_mandelbrot_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_linear_mandelbrot_wrapper<Policy>(state, B1::b1_1_for_each_linear_mandelbrot_omp);
}

#define B1_1_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER
BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_omp_wrapper, std::execution::sequenced_policy)->Name(
		BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(
		MAX_INPUT_SIZE, MAX_INPUT_SIZE);
\

BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_omp_wrapper, std::execution::parallel_policy)->Name(
		BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5,
																												 MAX_INPUT_SIZE);
#else
#define B1_1_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER
#endif

//region b1_2_for_each_quadratic
template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(state, B1::b1_2_for_each_quadratic);
}

#define B1_2_FOR_EACH_QUADRATIC_WRAPPER \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<15, 1<<15); \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::parallel_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15); \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::sequenced_policy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15);\
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::parallel_policy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15);
//endregion b1_2_for_each_quadratic

// region b1_2_for_each_quadratic_omp
#ifdef USE_OMP

template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_quadratic_wrapper<OuterPolicy, InnerPolicy>(state, B1::b1_2_for_each_quadratic_omp);
}

#define B1_2_FOR_EACH_QUADRATIC_OMP_WRAPPER \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_omp_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<15, 1<<15); \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_omp_wrapper,std::execution::parallel_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15); \
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_omp_wrapper,std::execution::sequenced_policy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15);\
        BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_omp_wrapper,std::execution::parallel_policy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15);
#else
#define B1_2_FOR_EACH_QUADRATIC_OMP_WRAPPER
#endif
// endregion b1_2_for_each_quadratic_omp


//region b1_2_for_each_quadratic_mandelbrot
template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_mandelbrot_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(state,
																				  B1::b1_2_for_each_quadratic_mandelbrot);
}

#define B1_2_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer) \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<13, 1<<13); \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_wrapper,outer,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<13);
//endregion b1_2_for_each_quadratic_mandelbrot


//region b1_2_for_each_quadratic_mandelbrot_omp
#ifdef USE_OMP
template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_mandelbrot_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_quadratic_mandelbrot_wrapper<OuterPolicy, InnerPolicy>(state,
																				  B1::b1_2_for_each_quadratic_mandelbrot_omp);
}

#define B1_2_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(outer) \
	BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_omp_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_omp_outer_std::execution::sequenced_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<13, 1<<13); \
	BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_omp_wrapper,outer,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_omp_outer_" xstr(outer) "_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<13);
#else
#define B1_2_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(outer)
#endif
//endregion b1_2_for_each_quadratic_mandelbrot_omp

//region b1_4_for_each_exponential
template<class Policy>
static void b1_4_for_each_exponential_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_exponential_wrapper<Policy>(state, B1::b1_4_for_each_exponential);
}

#define B1_4_FOR_EACH_EXPONENTIAL_WRAPPER \
	BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
	BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5);
//endregion b1_4_for_each_exponential

//region b1_4_for_each_exponential_omp
#ifdef USE_OMP
template<class Policy>
static void b1_4_for_each_exponential_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_exponential_wrapper<Policy>(state, B1::b1_4_for_each_exponential_omp);
}

#define B1_4_FOR_EACH_EXPONENTIAL_OMP_WRAPPER \
	BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_omp_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
	BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_omp_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5);
#else
#define B1_4_FOR_EACH_EXPONENTIAL_OMP_WRAPPER
#endif

#ifdef ONLY_GPU


#define NESTED_PARALLELISM_GROUP \
							\
	B1_1_FOR_EACH_LINEAR_MANDELBROT_WRAPPER


#else

// Register the function as a benchmark
#define NESTED_PARALLELISM_GROUP \
        B1_1_FOR_EACH_LINEAR_WRAPPER \
        B1_1_FOR_EACH_LINEAR_OMP_WRAPPER \
        B1_1_FOR_EACH_LINEAR_MANDELBROT_WRAPPER \
        B1_1_FOR_EACH_LINEAR_MANDELBROT_OMP_WRAPPER \
        B1_2_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(std::execution::parallel_policy) \
        B1_2_FOR_EACH_QUADRATIC_MANDELBROT_OMP_WRAPPER(std::execution::parallel_policy) \
        B1_4_FOR_EACH_EXPONENTIAL_WRAPPER\
        B1_4_FOR_EACH_EXPONENTIAL_OMP_WRAPPER

#endif

#endif //PSTL_BENCH_B1_GROUP_H
