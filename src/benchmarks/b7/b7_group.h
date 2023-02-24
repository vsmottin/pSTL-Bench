
#ifndef MASTER_BENCHMARKS_B7_GROUP_H
#define MASTER_BENCHMARKS_B7_GROUP_H

#include <benchmark/benchmark.h>
#include <vector>
#include <execution>
#include <cassert>
#include <iostream>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b7_1_copy_vs_for_each.h"
#include "b7_2_all_off_vs_transform_reduce.h"
#include "b7_3_count_if_vs_transform_reduce_vs_for_each.h"

//region b7_copy_vs_for_each

template<class Policy>
static void b7_1_copy(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    std::vector res(size, -1);


    for (auto _: state) {
        B7::b7_1_copy(execution_policy, vec1, res);

        state.PauseTiming();
        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_custom_copy_with_foreach(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);
    std::vector res(size, -1);


    for (auto _: state) {
        B7::b7_custom_copy_with_foreach(execution_policy, vec1, res);

        state.PauseTiming();
        assert(std::equal(vec1.begin(), vec1.end(), res.begin()));
        state.ResumeTiming();
    }
}

//endregion b7_copy_vs_for_each


//region b7_2_all_off_vs_transform_reduce

//region b7_2_all_of

template<class Policy>
static void b7_2_all_of_all_true(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return val >= 0; });

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_2_all_of_first_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return val > 10000; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_2_all_of_last_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_2_all_of(execution_policy, vec1, [size](const int &val) { return val < size - 1; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_2_all_of_auto_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_2_all_of(execution_policy, vec1, [](const int &val) { return false; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

#define B7_2_ALL_OF_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_all_true,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_all_true_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_first_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_first_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_last_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_last_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_2_all_of_auto_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_2_all_of_auto_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \

//endregion b7_2_all_of

//region b7_custom_all_of_with_transform_reduce


template<class Policy>
static void b7_custom_all_of_with_transform_reduce_all_true(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                    [](const int &val) { return val >= 0; });

        state.PauseTiming();
        assert((res == true));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_custom_all_of_with_transform_reduce_first_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                    [](const int &val) { return val > 10000; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_custom_all_of_with_transform_reduce_last_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                    [size](const int &val) { return val < size - 1; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_custom_all_of_with_transform_reduce_auto_false(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_custom_all_of_with_transform_reduce(execution_policy, vec1,
                                                                    [](const int &val) { return false; });

        state.PauseTiming();
        assert((res == false));
        state.ResumeTiming();
    }
}

#define B7_2_ALL_OFF_LOGIC_WITH_TRANSFORM_REDUCE_BENCHMARKS \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_all_true,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_all_true_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_all_true,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_all_true_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_all_true,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_all_true_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_all_true,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_all_true_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_first_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_first_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_first_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_first_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_first_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_first_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_first_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_first_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_last_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_last_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_last_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_last_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_last_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_last_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_last_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_last_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \
                               \
                               \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_auto_false,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_auto_false_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_auto_false,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_auto_false_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_auto_false,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_auto_false_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_all_of_with_transform_reduce_auto_false,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_all_of_with_transform_reduce_auto_false_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);          \


//endregion b7_custom_all_of_with_transform_reduce

//endregion b7_2_all_off_vs_transform_reduce


//region b7_3_count_if_vs_transform_reduce

//region b7_3_count_if

template<class Policy>
static void b7_3_count_if_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_count_if(execution_policy, vec1,
                                           [](const int &val) { return val >= -1; });

        state.PauseTiming();
        assert((res == size));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_3_count_if_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_count_if(execution_policy, vec1,
                                           [half_size](const int &val) { return val >= half_size; });

        state.PauseTiming();
        assert((res >= half_size));
        state.ResumeTiming();
    }
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

    std::vector<B7::Orders> input_data(size);

    auto n = 0;
    const auto values = suite::generate_increment<suite::int_vec>(size, 1);

    std::generate(input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        const auto res = B7::b7_3_count_if(execution_policy, input_data,
                                           [](const B7::Orders &val) { return val.price * val.quantity >= cutoff; });

        state.PauseTiming();
        assert((res == expected_result));
        state.ResumeTiming();
    }
}

//endregion b7_3_count_if


//region b7_3_custom_count_if_with_transform_reduce

template<class Policy>
static void b7_3_custom_count_if_with_transform_reduce_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, vec1,
                                                                        [](const int &val) { return val >= -1; });

        state.PauseTiming();
        assert((res == size));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_3_custom_count_if_with_transform_reduce_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, vec1,
                                                                        [half_size](const int &val) {
                                                                            return val >= half_size;
                                                                        });

        state.PauseTiming();
        assert((res >= half_size));
        state.ResumeTiming();
    }
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

    std::vector<B7::Orders> input_data(size);

    auto n = 0;
    const auto values = suite::generate_increment<suite::int_vec>(size, 1);

    std::generate(input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_transform_reduce(execution_policy, input_data,
                                                                        [](const B7::Orders &val) {
                                                                            return val.price * val.quantity >= cutoff;
                                                                        });

        state.PauseTiming();
        assert((res == expected_result));
        state.ResumeTiming();
    }
}

//endregion b7_3_custom_count_if_with_transform_reduce


//region b7_3_custom_count_if_with_for_each

template<class Policy>
static void b7_3_custom_count_if_with_for_each_all_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, vec1,
                                                                [](const int &val) { return val >= -1; });

        state.PauseTiming();
        assert((res == size));
        state.ResumeTiming();
    }
}

template<class Policy>
static void b7_3_custom_count_if_with_for_each_half_hit(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &size = state.range(0);
    const auto half_size = int(size / 2);

    // vector with values [0,size)
    const auto vec1 = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, vec1,
                                                                [half_size](const int &val) {
                                                                    return val >= half_size;
                                                                });

        state.PauseTiming();
        assert((res >= half_size));
        state.ResumeTiming();
    }
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

    std::vector<B7::Orders> input_data(size);

    auto n = 0;
    const auto values = suite::generate_increment<suite::int_vec>(size, 1);

    std::generate(input_data.begin(), input_data.end(),
                  [&]() { return B7::Orders{values[n++], default_quantity}; });
    //endregion generate order data

    for (auto _: state) {
        const auto res = B7::b7_3_custom_count_if_with_for_each(execution_policy, input_data,
                                                                [](const B7::Orders &val) {
                                                                    return val.price * val.quantity >= cutoff;
                                                                });

        state.PauseTiming();
        assert((res == expected_result));
        state.ResumeTiming();
    }
}

//endregion b7_3_custom_count_if_with_for_each

//endregion b7_3_count_if_vs_transform_reduce


#define B7_GROUP_BENCHMARKS \
                            \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_1_copy_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_1_copy,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_1_copy_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_custom_copy_with_foreach,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_custom_copy_with_foreach_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
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
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_all_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_all_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_half_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_half_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_count_if_orders_struct,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_count_if_orders_struct_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_all_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_all_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_half_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_half_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_transform_reduce_orders_struct,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_transform_reduce_orders_struct_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_all_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_all_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_half_hit,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_half_hit_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\
                            \
                            \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);     \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::parallel_unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20); \
        BENCHMARK_TEMPLATE1(b7_3_custom_count_if_with_for_each_orders_struct,std::execution::unsequenced_policy)->Name(BENCHMARK_NAME("b7_3_custom_count_if_with_for_each_orders_struct_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 20);\


#endif //MASTER_BENCHMARKS_B7_GROUP_H
