#ifndef PSTL_BENCH_B1_5_GROUP_H
#define PSTL_BENCH_B1_5_GROUP_H

#include <benchmark/benchmark.h>

#include "../b1_utils.h"

#include "b1_5_for_each_exponential.h"

#ifdef USE_OMP
#include "b1_5_for_each_exponential_omp.h"
#endif

#ifdef USE_GNU_PSTL
#include "b1_5_for_each_exponential_gnu.h"
#endif

//region b1_5_for_each_exponential
template<class Policy>
static void b1_5_for_each_exponential_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_exponential_wrapper<Policy>(state, B1::b1_5_for_each_exponential);
}

#define B1_5_FOR_EACH_EXPONENTIAL_WRAPPER \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5);
//endregion b1_5_for_each_exponential

//region b1_5_for_each_exponential_omp
#ifdef USE_OMP
template<class Policy>
static void b1_5_for_each_exponential_omp_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_exponential_wrapper<Policy>(state, B1::b1_5_for_each_exponential_omp);
}

#define B1_5_FOR_EACH_EXPONENTIAL_OMP_WRAPPER \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_omp_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_omp_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5);
#else
#define B1_5_FOR_EACH_EXPONENTIAL_OMP_WRAPPER
#endif
//endregion b1_5_for_each_exponential_omp

//region b1_5_for_each_exponential_gnu
#ifdef USE_GNU_PSTL
template<class Policy>
static void b1_5_for_each_exponential_gnu_wrapper (benchmark::State & state) {
	B1::benchmark_for_each_exponential_wrapper<Policy>(state, B1::b1_5_for_each_exponential_gnu);
}

#define B1_5_FOR_EACH_EXPONENTIAL_GNU_WRAPPER \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_gnu_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_gnu_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
	BENCHMARK_TEMPLATE1(b1_5_for_each_exponential_gnu_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_5_for_each_exponential_gnu_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5);
#else
#define B1_5_FOR_EACH_EXPONENTIAL_GNU_WRAPPER
#endif
//endregion b1_5_for_each_exponential_gnu


#define B1_5_FOR_EACH_EXPONENTIAL_GROUP \
	B1_5_FOR_EACH_EXPONENTIAL_WRAPPER \
	B1_5_FOR_EACH_EXPONENTIAL_OMP_WRAPPER \
	B1_5_FOR_EACH_EXPONENTIAL_GNU_WRAPPER

#endif //PSTL_BENCH_B1_5_GROUP_H
