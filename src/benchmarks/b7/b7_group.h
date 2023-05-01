
#ifndef MASTER_BENCHMARKS_B7_GROUP_H
#define MASTER_BENCHMARKS_B7_GROUP_H

#include <chrono>
#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <cassert>
#include <iostream>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "../../parallel_allocator.h"

#include "b7_1_copy_vs_for_each.h"
#include "b7_2_all_off_vs_transform_reduce.h"
#include "b7_3_count_if_vs_transform_reduce_vs_for_each.h"
#include "b7_4_stencil_transform_vs_for_each.h"
#include "b7_5_scalar_transform_vs_for_each.h"
#include "b7_6_serial_transform_reduce_vs_transform_reduce.h"


//region b7_copy_vs_for_each

template<class Policy>
static void b7_1_copy(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    auto res = suite::get_vec<Policy>(size);

    for (auto _: state) {

        WRAP_TIMING(B7::b7_1_copy(execution_policy, vec1, res);)

        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_1_custom_copy_with_foreach(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    auto res = suite::get_vec<Policy>(size);

    const auto &view = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B7::b7_1_custom_copy_with_foreach(execution_policy, vec1, view, res);)

        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_copy_vs_for_each


//region b7_2_all_off_vs_transform_reduce

//region b7_2_all_of

template<class Policy>
static void b7_2_all_of_all_true(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return val >= 0; });)

        assert((res == true));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_all_of_first_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(
                const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return val > 10000; });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_all_of_last_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_all_of(execution_policy, vec1,
                                                     [size](const int &val) { return val < size - 1; });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_all_of_auto_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return false; });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

#define B7_2_ALL_OF_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \

//endregion b7_2_all_of

//region b7_custom_all_of_with_transform_reduce


template<class Policy>
static void b7_2_custom_all_of_with_transform_reduce_all_true(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                                  [](const int &val) {
                                                                                      return val >= 0;
                                                                                  });)

        assert((res == true));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_custom_all_of_with_transform_reduce_first_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                                  [](const int &val) {
                                                                                      return val > 10000;
                                                                                  });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_custom_all_of_with_transform_reduce_last_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                                  [size](const int &val) {
                                                                                      return val < size - 1;
                                                                                  });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_2_custom_all_of_with_transform_reduce_auto_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_2_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                                  [](const int &val) { return false; });)

        assert((res == false));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

#define B7_2_ALL_OFF_LOGIC_WITH_TRANSFORM_REDUCE_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_all_true,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_all_true_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_all_true,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_all_true_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_first_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_first_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_first_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_first_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_last_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_last_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_last_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_last_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_auto_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_auto_false_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_2_custom_all_of_with_transform_reduce_auto_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_custom_all_of_with_transform_reduce_auto_false_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \


//endregion b7_custom_all_of_with_transform_reduce

//endregion b7_2_all_off_vs_transform_reduce


//region b7_3_count_if_vs_transform_reduce

//region b7_3_count_if

template<class Policy>
static void b7_3_count_if_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_count_if(execution_policy, vec1,
                                                       [](const int &val) { return val >= -1; });)

        assert((res == size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_count_if_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_count_if(execution_policy, vec1,
                                                       [half_size](const int &val) { return val >= half_size; });)

        assert((res >= half_size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_count_if_orders_struct(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    //region generate order data
    constexpr auto default_quantity = 5;
    constexpr auto cutoff = 40;

    // we calculate the number of elements that satisfy condition (val.price * val.quantity >= cutoff)
    const auto expected_result = std::max(size - (cutoff / default_quantity), static_cast<decltype(size)>(0));

    auto input_data = suite::get_vec<Policy, suite::vec<B7::Orders, Policy>>(size);

    std::atomic<std::size_t> n{0};
    const auto values = suite::generate_increment(execution_policy, size, 1);

    std::generate(execution_policy, input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_count_if(execution_policy, input_data,
                                                       [](const B7::Orders &val) {
                                                           return val.price * val.quantity >= cutoff;
                                                       });)

        assert((res == expected_result));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(B7::Orders) *
                                         (int64_t(input_data.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_3_count_if


//region b7_3_custom_count_if_with_transform_reduce

template<class Policy>
static void b7_3_custom_count_if_with_transform_reduce_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, vec1,
                                                                                    [](const int &val) {
                                                                                        return val >= -1;
                                                                                    });)

        assert((res == size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_custom_count_if_with_transform_reduce_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, vec1,
                                                                                    [half_size](const int &val) {
                                                                                        return val >= half_size;
                                                                                    });)

        assert((res >= half_size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_custom_count_if_with_transform_reduce_orders_struct(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    //region generate order data
    constexpr auto default_quantity = 5;
    constexpr auto cutoff = 40;

    // we calculate the number of elements that satisfy condition (val.price * val.quantity >= cutoff)
    const auto expected_result = std::max(size - (cutoff / default_quantity), static_cast<decltype(size)>(0));
    auto input_data = suite::get_vec<Policy, suite::vec<B7::Orders, Policy>>(size);

    std::atomic<int> n{0};
    const auto values = suite::generate_increment(execution_policy, size, 1);

    std::generate(execution_policy, input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, input_data,
                                                                                    [](const B7::Orders &val) {
                                                                                        return val.price *
                                                                                               val.quantity >= cutoff;
                                                                                    });)

        assert((res == expected_result));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(B7::Orders) *
                                         (int64_t(input_data.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_3_custom_count_if_with_transform_reduce


//region b7_3_custom_count_if_with_for_each

template<class Policy>
static void b7_3_custom_count_if_with_for_each_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, vec1,
                                                                            [](const int &val) { return val >= -1; });)

        assert((res == size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_custom_count_if_with_for_each_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, vec1,
                                                                            [half_size](const int &val) {
                                                                                return val >= half_size;
                                                                            });)

        assert((res >= half_size));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_3_custom_count_if_with_for_each_orders_struct(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    //region generate order data
    constexpr auto default_quantity = 5;
    constexpr auto cutoff = 40;

    // we calculate the number of elements that satisfy condition (val.price * val.quantity >= cutoff)
    const auto expected_result = std::max(size - (cutoff / default_quantity), static_cast<decltype(size)>(0));
    auto input_data = suite::get_vec<Policy, suite::vec<B7::Orders, Policy>>(size);

    std::atomic<int> n{0};
    const auto values = suite::generate_increment(execution_policy, size, 1);

    std::generate(execution_policy, input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, input_data,
                                                                            [](const B7::Orders &val) {
                                                                                return val.price * val.quantity >=
                                                                                       cutoff;
                                                                            });)

        assert((res == expected_result));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(B7::Orders) *
                                         (int64_t(input_data.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_3_custom_count_if_with_for_each

//endregion b7_3_count_if_vs_transform_reduce


//region b7_4_stencil_transform_vs_for_each

template<class Policy>
static void b7_4_stencil_transform_number_to_neightbours_stdev(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_uniform_dist_vec<Policy>(size, 1, 100);

    auto res = suite::get_vec<Policy, suite::double_vec<Policy>>(size - 1);

    const auto &view = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B7::b7_4_stencil_transform_number_to_neightbours_stdev(execution_policy, vec1, view, res);)

        assert((res[0] >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (3 * int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_4_stencil_for_each_to_neightbours_stdev(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_uniform_dist_vec<Policy>(size, 1, 100);
    auto res = suite::get_vec<Policy, suite::double_vec<Policy>>(size - 1);

    //const auto &view = std::views::iota(0, static_cast<int>(vec1.size()));
    const auto &view = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B7::b7_4_stencil_for_each_to_neightbours_stdev(execution_policy, vec1, view, res);)

        assert((res[0] >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (3 * int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_4_stencil_transform_vs_for_eac

//region b7_5_scalar_transform_vs_for_each

template<class Policy>
static void b7_5_scalar_transform_number(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_uniform_dist_vec<Policy>(size, 1, 100);

    auto res = suite::get_vec<Policy>(size);

    for (auto _: state) {
        WRAP_TIMING(B7::b7_5_scalar_transform_number(execution_policy, vec1, res);)

        assert((res[0] >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_5_scalar_for_each(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_uniform_dist_vec<Policy>(size, 1, 100);

    auto res = suite::get_vec<Policy>(size);

    const auto &view = suite::generate_increment(execution_policy, size, 1);

    for (auto _: state) {
        WRAP_TIMING(B7::b7_5_scalar_for_each(execution_policy, vec1, view, res);)

        assert((res[0] >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(int) *
                                         (int64_t(vec1.size()) + int64_t(res.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_5_scalar_transform_vs_for_each


//region b7_6_serial_transform_reduce_vs_transform_reduce

template<class Policy>
static void b7_6_serial_transform_reduce(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto values = suite::generate_uniform_dist_vec<Policy>(2, 1, 10);

    auto input_data = suite::get_vec<Policy, suite::vec<B7::Pixel, Policy>>(size);
    std::generate(execution_policy, input_data.begin(), input_data.end(),
                  [n = 0, &values]() { return B7::Pixel{values[n], values[n], values[n]}; });


    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_6_serial_transform_reduce(execution_policy, input_data);)

        assert((res >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(B7::Pixel) *
                                         (2 * int64_t(input_data.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

template<class Policy>
static void b7_6_transform_reduce(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto values = suite::generate_uniform_dist_vec<Policy>(size, 1, 10);

    auto input_data = suite::get_vec<Policy, suite::vec<B7::Pixel, Policy>>(size);
    std::generate(execution_policy, input_data.begin(), input_data.end(),
                  [n = 0, &values]() { return B7::Pixel{values[n], values[n], values[n]}; });


    for (auto _: state) {
        WRAP_TIMING(const auto res = B7::b7_6_transform_reduce(execution_policy, input_data);)

        assert((res >= 0));
    }

    // https://ccfd.github.io/courses/hpc_lab01.html
    const int64_t actual_size_in_bytes = sizeof(B7::Orders) *
                                         (int64_t(input_data.size()));

    state.SetBytesProcessed(int64_t(state.iterations()) * actual_size_in_bytes);
}

//endregion b7_6_serial_transform_reduce_vs_transform_reduce

#ifdef ONLY_GPU

#define B7_GROUP_BENCHMARKS \
                            \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_1_copy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_4_stencil_transform_number_to_neightbours_stdev,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_4_stencil_transform_number_to_neightbours_stdev_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_4_stencil_transform_number_to_neightbours_stdev,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_4_stencil_transform_number_to_neightbours_stdev_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \



#else

#define B7_GROUP_BENCHMARKS \
                            \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_1_copy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_1_custom_copy_with_foreach,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_1_custom_copy_with_foreach_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_1_custom_copy_with_foreach,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_1_custom_copy_with_foreach_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
                            \
        B7_2_ALL_OF_BENCHMARKS                                                                                                                              \
                            \
                            \
        B7_2_ALL_OFF_LOGIC_WITH_TRANSFORM_REDUCE_BENCHMARKS \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_4_stencil_transform_number_to_neightbours_stdev,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_4_stencil_transform_number_to_neightbours_stdev_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_4_stencil_transform_number_to_neightbours_stdev,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_4_stencil_transform_number_to_neightbours_stdev_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_4_stencil_for_each_to_neightbours_stdev,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_4_stencil_for_each_to_neightbours_stdev_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_4_stencil_for_each_to_neightbours_stdev,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_4_stencil_for_each_to_neightbours_stdev_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_5_scalar_transform_number,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_5_scalar_transform_number_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_5_scalar_transform_number,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_5_scalar_transform_number_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_5_scalar_for_each,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_5_scalar_for_each_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_5_scalar_for_each,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_5_scalar_for_each_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_6_serial_transform_reduce,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_6_serial_transform_reduce_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_6_serial_transform_reduce,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_6_serial_transform_reduce_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_6_transform_reduce,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_6_transform_reduce_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
        BENCHMARK_TEMPLATE1(b7_6_transform_reduce,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_6_transform_reduce_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, MAX_INPUT_SIZE);     \


#endif

#endif //MASTER_BENCHMARKS_B7_GROUP_H
