
#ifndef PSTL_BENCH_B5_GROUP_H
#define PSTL_BENCH_B5_GROUP_H

#include <benchmark/benchmark.h>
#include <cassert>
#include <chrono>
#include <deque>
#include <execution>
#include <iostream>
#include <list>
#include <vector>

#include <benchmark_prefix.h>
#include <benchmark_utils.h>

#include "b5_1_find.h"
#include "b5_2_partition.h"
#include "b5_3_unique_copy.h"
#include "b5_4_minmax_element.h"

#ifdef USE_OMP

#include "b5_1_find_omp.h"

#endif

#ifdef USE_GNU_PSTL

#include "b5_1_find_gnu.h"
#include "b5_2_partition_gnu.h"
#include "b5_3_unique_copy_gnu.h"

#endif

#include "b5_utils.h"

//region b5_1_find
template<class Policy>
static void b5_1_find_first_entry(benchmark::State & state)
{
	B5::benchmark_find_wrapper<Policy>(state, B5::b5_1_find);
}

template<class Policy>
static void b5_1_find_last_entry(benchmark::State & state)
{
	B5::benchmark_find_last_wrapper<Policy>(state, B5::b5_1_find);
}

template<class Policy>
static void b5_1_find_non_existing_entry(benchmark::State & state)
{
	B5::benchmark_find_non_existing_wrapper<Policy>(state, B5::b5_1_find);
}

#define B5_1_FIND_WRAPPER                                                               \
                                                                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_first_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_first_entry_seq"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_first_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_first_entry_par"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                \
                                                                                        \
                                                                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_last_entry, std::execution::sequenced_policy)         \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_last_entry_seq"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_last_entry, std::execution::parallel_policy)          \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_last_entry_par"))             \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                \
                                                                                        \
                                                                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_non_existing_entry_seq"))     \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_1_find_std::vector<int>_non_existing_entry_par"))     \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 2, MAX_INPUT_SIZE);

//endregion b5_1_find

//region b5_1_find_omp
#ifdef USE_OMP

template<class Policy>
static void b5_1_find_omp_first_entry(benchmark::State & state)
{
	B5::benchmark_find_wrapper<Policy>(state, B5::b5_1_find_omp);
}

template<class Policy>
static void b5_1_find_omp_last_entry(benchmark::State & state)
{
	B5::benchmark_find_last_wrapper<Policy>(state, B5::b5_1_find_omp);
}

template<class Policy>
static void b5_1_find_omp_non_existing_entry(benchmark::State & state)
{
	B5::benchmark_find_non_existing_wrapper<Policy>(state, B5::b5_1_find_omp);
}

#define B5_1_FIND_OMP_WRAPPER                                                              \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_omp_first_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_first_entry_seq"))           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_omp_first_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_first_entry_par"))           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                   \
                                                                                           \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_omp_last_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_last_entry_seq"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_omp_last_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_last_entry_par"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                   \
                                                                                           \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry, std::execution::sequenced_policy)    \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_non_existing_entry_seq"))    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_omp_non_existing_entry, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("b5_1_find_omp_std::vector<int>_non_existing_entry_par"))    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B5_1_FIND_OMP_WRAPPER
#endif

//region b5_1_find_gnu
#ifdef USE_GNU_PSTL

template<class Policy>
static void b5_1_find_gnu_first_entry(benchmark::State & state)
{
	B5::benchmark_find_wrapper<Policy>(state, B5::b5_1_find_gnu);
}

template<class Policy>
static void b5_1_find_gnu_last_entry(benchmark::State & state)
{
	B5::benchmark_find_last_wrapper<Policy>(state, B5::b5_1_find_gnu);
}

template<class Policy>
static void b5_1_find_gnu_non_existing_entry(benchmark::State & state)
{
	B5::benchmark_find_non_existing_wrapper<Policy>(state, B5::b5_1_find_gnu);
}

#define B5_1_FIND_GNU_WRAPPER                                                              \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_gnu_first_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_first_entry_seq"))           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_gnu_first_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_first_entry_par"))           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                   \
                                                                                           \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_gnu_last_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_last_entry_seq"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_gnu_last_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_last_entry_par"))            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                                   \
                                                                                           \
                                                                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_non_existing_entry, std::execution::sequenced_policy)    \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_non_existing_entry_seq"))    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                           \
	BENCHMARK_TEMPLATE1(b5_1_find_gnu_non_existing_entry, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("b5_1_find_gnu_std::vector<int>_non_existing_entry_par"))    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                            \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B5_1_FIND_GNU_WRAPPER
#endif
//endregion b5_1_find_gnu

//region b5_2_partition
template<class Policy>
static void b5_2_partition_wrapper(benchmark::State & state)
{
	B5::benchmark_partition_wrapper<Policy>(state, B5::b5_2_partition);
}

#define B5_2_PARTITION_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b5_2_partition_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_2_partition_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                  \
	BENCHMARK_TEMPLATE1(b5_2_partition_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_2_partition_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                   \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b5_2_partition

//region b5_2_partition_gnu
#ifdef USE_GNU_PSTL

template<class Policy>
static void b5_2_partition_gnu_wrapper(benchmark::State & state)
{
	B5::benchmark_partition_wrapper<Policy>(state, B5::b5_2_partition_gnu);
}

#define B5_2_PARTITION_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b5_2_partition_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_2_partition_gnu_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(b5_2_partition_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_2_partition_gnu_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B5_2_PARTITION_GNU_WRAPPER
#endif
//endregion b5_2_partition_gnu

//region b5_3_unique_copy
template<class Policy>
static void b5_3_unique_copy_default_wrapper(benchmark::State & state)
{
	B5::benchmark_unique_copy_default_wrapper<Policy>(state, B5::b5_3_unique_copy_default);
}

#define B5_3_UNIQUE_COPY_DEFAULT_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b5_3_unique_copy_default_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_3_unique_copy_default_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                            \
	BENCHMARK_TEMPLATE1(b5_3_unique_copy_default_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_3_unique_copy_default_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                             \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b5_3_unique_copy

//region b5_3_unique_copy_gnu
#ifdef USE_GNU_PSTL

template<class Policy>
static void b5_3_unique_copy_gnu_wrapper(benchmark::State & state)
{
	B5::benchmark_unique_copy_default_wrapper<Policy>(state, B5::b5_3_unique_copy_gnu);
}

#define B5_3_UNIQUE_COPY_GNU_WRAPPER                                                    \
	BENCHMARK_TEMPLATE1(b5_3_unique_copy_gnu_wrapper, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_3_unique_copy_gnu_seq"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                        \
	BENCHMARK_TEMPLATE1(b5_3_unique_copy_gnu_wrapper, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_3_unique_copy_gnu_par"))                              \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                         \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define B5_3_UNIQUE_COPY_GNU_WRAPPER
#endif
//endregion b5_3_unique_copy_gnu

//region b5_4_minmax_element
template<class Policy>
static void b5_4_minmax_element_all_equal(benchmark::State & state)
{
	B5::benchmark_minmax_element_all_equal_wrapper<Policy>(state, B5::b5_4_minmax_element);
}

#define B5_4_MINMAX_ELEMENT_ALL_EQUAL_WRAPPER                                            \
	BENCHMARK_TEMPLATE1(b5_4_minmax_element_all_equal, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_4_minmax_element_all_equal_seq"))                      \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                         \
	BENCHMARK_TEMPLATE1(b5_4_minmax_element_all_equal, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_4_minmax_element_all_equal_par"))                      \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                          \
	    ->Range(1 << 2, MAX_INPUT_SIZE);


template<class Policy>
static void b5_4_minmax_element_increasing(benchmark::State & state)
{
	B5::benchmark_minmax_element_increasing_wrapper<Policy>(state, B5::b5_4_minmax_element);
}

#define B5_4_MINMAX_ELEMENT_INCREASING_WRAPPER                                            \
	BENCHMARK_TEMPLATE1(b5_4_minmax_element_increasing, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("b5_4_minmax_element_increasing_seq"))                      \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                          \
	BENCHMARK_TEMPLATE1(b5_4_minmax_element_increasing, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("b5_4_minmax_element_increasing_par"))                      \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                           \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
//endregion b5_4_minmax_element


#ifdef ONLY_GPU

#define SPECIALIZED_TECHNIQUES_GROUP

#else

// Register the function as a benchmark
#define SPECIALIZED_TECHNIQUES_GROUP      \
                                          \
	B5_1_FIND_WRAPPER                     \
	B5_1_FIND_OMP_WRAPPER                 \
	B5_1_FIND_GNU_WRAPPER                 \
                                          \
	B5_2_PARTITION_WRAPPER                \
	B5_2_PARTITION_GNU_WRAPPER            \
                                          \
	B5_3_UNIQUE_COPY_DEFAULT_WRAPPER      \
	B5_3_UNIQUE_COPY_GNU_WRAPPER          \
                                          \
                                          \
	B5_4_MINMAX_ELEMENT_ALL_EQUAL_WRAPPER \
	B5_4_MINMAX_ELEMENT_INCREASING_WRAPPER

#endif

#endif //PSTL_BENCH_B5_GROUP_H
