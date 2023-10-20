
#ifndef PSTL_BENCH_FIND_GROUP_H
#define PSTL_BENCH_FIND_GROUP_H

#include "find_utils.h"

#include "find_std.h"

#ifdef USE_OMP

#include "find_omp.h"

#endif

#ifdef USE_GNU_PSTL

#include "find_gnu.h"

#endif

//region find
template<class Policy>
static void find_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_std);
}

template<class Policy>
static void find_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_std);
}

#define FIND_STD_WRAPPER                                                           \
                                                                                   \
	BENCHMARK_TEMPLATE1(find_random_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME("std::find_random_entry_seq"))                       \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_random_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("std::find_random_entry_par"))                       \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                           \
                                                                                   \
                                                                                   \
	BENCHMARK_TEMPLATE1(find_first_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("std::find_first_entry_seq"))                        \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_first_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("std::find_first_entry_par"))                        \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                           \
                                                                                   \
                                                                                   \
	BENCHMARK_TEMPLATE1(find_last_entry, std::execution::sequenced_policy)         \
	    ->Name(BENCHMARK_NAME("std::find_last_entry_seq"))                         \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_last_entry, std::execution::parallel_policy)          \
	    ->Name(BENCHMARK_NAME("std::find_last_entry_par"))                         \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                           \
                                                                                   \
                                                                                   \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::sequenced_policy) \
	    ->Name(BENCHMARK_NAME("std::find_non_existing_entry_seq"))                 \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                   \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::parallel_policy)  \
	    ->Name(BENCHMARK_NAME("std::find_non_existing_entry_par"))                 \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                    \
	    ->Range(1 << 2, MAX_INPUT_SIZE);

//endregion find

//region find_omp
#ifdef USE_OMP

template<class Policy>
static void find_omp_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_omp);
}

template<class Policy>
static void find_omp_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_omp);
}

template<class Policy>
static void find_omp_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_omp);
}

template<class Policy>
static void find_omp_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_omp);
}

#define FIND_OMP_WRAPPER                                                              \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_omp_random_entry, std::execution::sequenced_policy)      \
	    ->Name(BENCHMARK_NAME("omp::find_random_entry_seq"))                          \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_omp_random_entry, std::execution::parallel_policy)       \
	    ->Name(BENCHMARK_NAME("omp::find_random_entry_par"))                          \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_omp_first_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME("omp::find_first_entry_seq"))                           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_omp_first_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("omp::find_first_entry_par"))                           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_omp_last_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("omp::find_last_entry_seq"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_omp_last_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("omp::find_last_entry_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::sequenced_policy)    \
	    ->Name(BENCHMARK_NAME("omp::find_non_existing_entry_seq"))                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_omp_non_existing_entry, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("omp::find_non_existing_entry_par"))                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define FIND_OMP_WRAPPER
#endif

//region find_gnu
#ifdef USE_GNU_PSTL

template<class Policy>
static void find_gnu_random_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_random_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_first_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_first_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_last_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_last_wrapper<Policy>(state, benchmark_find::find_gnu);
}

template<class Policy>
static void find_gnu_non_existing_entry(benchmark::State & state)
{
	benchmark_find::benchmark_find_non_existing_wrapper<Policy>(state, benchmark_find::find_gnu);
}

#define FIND_GNU_WRAPPER                                                              \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_gnu_random_entry, std::execution::sequenced_policy)      \
	    ->Name(BENCHMARK_NAME("gnu::find_random_entry_seq"))                          \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_gnu_random_entry, std::execution::parallel_policy)       \
	    ->Name(BENCHMARK_NAME("gnu::find_random_entry_par"))                          \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_gnu_first_entry, std::execution::sequenced_policy)       \
	    ->Name(BENCHMARK_NAME("gnu::find_first_entry_seq"))                           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_gnu_first_entry, std::execution::parallel_policy)        \
	    ->Name(BENCHMARK_NAME("gnu::find_first_entry_par"))                           \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_gnu_last_entry, std::execution::sequenced_policy)        \
	    ->Name(BENCHMARK_NAME("gnu::find_last_entry_seq"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_gnu_last_entry, std::execution::parallel_policy)         \
	    ->Name(BENCHMARK_NAME("gnu::find_last_entry_par"))                            \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);                                              \
                                                                                      \
                                                                                      \
	BENCHMARK_TEMPLATE1(find_non_existing_entry, std::execution::sequenced_policy)    \
	    ->Name(BENCHMARK_NAME("gnu::find_non_existing_entry_seq"))                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE);                                      \
	BENCHMARK_TEMPLATE1(find_gnu_non_existing_entry, std::execution::parallel_policy) \
	    ->Name(BENCHMARK_NAME("gnu::find_non_existing_entry_par"))                    \
	    ->CUSTOM_STATISTICS->RangeMultiplier(2)                                       \
	    ->Range(1 << 2, MAX_INPUT_SIZE);
#else
#define FIND_GNU_WRAPPER
#endif
//endregion find_gnu


// Register the function as a benchmark
#define FIND_GROUP   \
	FIND_STD_WRAPPER \
	FIND_OMP_WRAPPER \
	FIND_GNU_WRAPPER


#endif //PSTL_BENCH_FIND_GROUP_H
