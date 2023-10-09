
#ifndef PSTL_BENCH_B6_GROUP_H
#define PSTL_BENCH_B6_GROUP_H

#include <chrono>
#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <cassert>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include "b6_utils.h"

#include "b6_1_inclusive_scan.h"
#include "b6_2_exclusive_scan.h"

#include "b6_1_inclusive_scan_omp.h"
#include "b6_2_exclusive_scan_omp.h"


//region b6_1_inclusive_scan
template<class Policy>
static void b6_1_inclusive_scan_wrapper (benchmark::State & state) {
	B6::benchmark_inclusive_scan_wrapper<Policy>(state, B6::b6_1_inclusive_scan);
}

#define B6_1_INCLUSIVE_SCAN_GROUP \
        BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b6_1_inclusive_scan


//region b6_1_inclusive_scan_omp
#ifdef USE_OMP

template<class Policy>
static void b6_1_inclusive_scan_omp_wrapper (benchmark::State & state) {
	B6::benchmark_inclusive_scan_wrapper<Policy>(state, B6::b6_1_inclusive_scan_omp);
}

#define B6_1_INCLUSIVE_SCAN_OMP_GROUP \
        BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_omp_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_omp_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B6_1_INCLUSIVE_SCAN_OMP_GROUP
#endif
//endregion b6_1_inclusive_scan_omp


//region b6_2_exclusive_scan
template<class Policy>
static void b6_2_exclusive_scan_wrapper (benchmark::State & state) {
	B6::benchmark_exclusive_scan_wrapper<Policy>(state, B6::b6_2_exclusive_scan);
}

#define B6_2_EXCLUSIVE_SCAN_GROUP \
        BENCHMARK_TEMPLATE1(b6_2_exclusive_scan_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b6_2_exclusive_scan_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b6_2_exclusive_scan_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b6_2_exclusive_scan_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);          \
//endregion b6_2_exclusive_scan


//region b6_2_exclusive_scan_omp
#ifdef USE_OMP

template<class Policy>
static void b6_2_exclusive_scan_omp_wrapper (benchmark::State & state) {
	B6::benchmark_exclusive_scan_wrapper<Policy>(state, B6::b6_2_exclusive_scan_omp);
}

#define B6_2_EXCLUSIVE_SCAN_OMP_GROUP \
        BENCHMARK_TEMPLATE1(b6_2_exclusive_scan_omp_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b6_2_exclusive_scan_omp_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b6_2_exclusive_scan_omp_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b6_2_exclusive_scan_omp_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B6_2_EXCLUSIVE_SCAN_OMP_GROUP
#endif
//endregion b6_2_exclusive_scan_omp

#ifdef ONLY_GPU

#define OPTIMIZED_SCAN_GROUP \
							\
		BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
		BENCHMARK_TEMPLATE1(b6_1_inclusive_scan_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b6_1_inclusive_scan_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \

#else

#define OPTIMIZED_SCAN_GROUP \
        B6_1_INCLUSIVE_SCAN_GROUP \
        B6_1_INCLUSIVE_SCAN_OMP_GROUP \
        B6_2_EXCLUSIVE_SCAN_GROUP \
        B6_2_EXCLUSIVE_SCAN_OMP_GROUP

#endif


#endif //PSTL_BENCH_B6_GROUP_H
