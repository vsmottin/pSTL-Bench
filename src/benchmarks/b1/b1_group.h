#ifndef MASTER_BENCHMARKS_B1_GROUP_H
#define MASTER_BENCHMARKS_B1_GROUP_H

#include <execution>
#include <ranges>
#include <benchmark/benchmark.h>

#include "../benchmark_prefix.h"
#include "../benchmark_utils.h"

#include "b1_1_for_each_linear.h"
#include "b1_2_for_each_quadratic.h"
#include "b1_4_for_each_exponential.h"
#include "b1_1_for_each_linear_mandelbrot.h"
#include "b1_2_for_each_quadratic_mandelbrot.h"

//region b1_1_for_each_linear

template<class Policy>
static void b1_1_for_each_linear_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    std::vector<double> x(state.range(0), 1);

    for (auto _: state) {
        B1::b1_1_for_each_linear(execution_policy, x);
    }
}

//endregion b1_1_for_each_linear

//region b1_1_for_each_linear_mandelbrot

template<class Policy>
static void b1_1_for_each_linear_mandelbrot_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto size = state.range(0);
    const auto x = suite::generate_increment<suite::int_vec>(size, 1);

    for (auto _: state) {
        B1::b1_1_for_each_linear_mandelbrot(execution_policy, x);
    }
}

#define B1_1_FOR_EACH_LINEAR_MANDELBROT_WRAPPER \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_mandelbrot_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_mandelbrot_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, MAX_INPUT_SIZE);  \

//endregion b1_1_for_each_linear_mandelbrot

//region b1_2_for_each_quadratic

template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_wrapper(benchmark::State &state) {
    constexpr auto outer_execution_policy = OuterPolicy{};
    constexpr auto inner_execution_policy = InnerPolicy{};

    const auto size = state.range(0);
    const auto input_data = suite::generate_increment<std::vector<double>>(size, 1, 0);

    for (auto _: state) {
        B1::b1_2_for_each_quadratic(outer_execution_policy, inner_execution_policy, input_data);
    }
}

//endregion b1_2_for_each_quadratic


//region b1_2_for_each_quadratic_mandelbrot

template<class OuterPolicy, class InnerPolicy>
static void b1_2_for_each_quadratic_mandelbrot_wrapper(benchmark::State &state) {
    constexpr auto outer_execution_policy = OuterPolicy{};
    constexpr auto inner_execution_policy = InnerPolicy{};

    const auto size = state.range(0);
    const auto input_data = suite::generate_increment<suite::int_vec>(size, 1, 0);

    for (auto _: state) {
        B1::b1_2_for_each_quadratic_mandelbrot(outer_execution_policy, inner_execution_policy, input_data);
    }
}

#define B1_2_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(outer) \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_outer_std::execution::sequenced_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<15, 1<<15); \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_mandelbrot_wrapper,outer,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_mandelbrot_outer_" xstr(outer) "_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15); \


//endregion b1_2_for_each_quadratic_mandelbrot


//region b1_4_for_each_exponential

template<class Policy>
static void b1_4_for_each_exponential_wrapper(benchmark::State &state) {
    constexpr auto execution_policy = Policy{};

    const auto &data = std::ranges::iota_view(1, static_cast<int>(state.range(0)));

    for (auto _: state) {
        B1::b1_4_for_each_exponential(execution_policy, data);
    }
}

//endregion b1_4_for_each_exponential


// Register the function as a benchmark
#define B1_GROUP_BENCHMARKS \
                            \
                            \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(MAX_INPUT_SIZE, MAX_INPUT_SIZE); \
    BENCHMARK_TEMPLATE1(b1_1_for_each_linear_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_1_for_each_linear_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, MAX_INPUT_SIZE); \
                            \
                            \
                            \
    B1_1_FOR_EACH_LINEAR_MANDELBROT_WRAPPER                                                                                                                                                              \
                            \
                            \
                            \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::sequenced_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1<<15, 1<<15); \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::parallel_policy,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::parallel_policy_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15); \
    BENCHMARK_TEMPLATE2(b1_2_for_each_quadratic_wrapper,std::execution::sequenced_policy,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_outer_std::execution::sequenced_policy_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1<<15); \
                            \
                            \
                            \
    B1_2_FOR_EACH_QUADRATIC_MANDELBROT_WRAPPER(std::execution::parallel_policy) \
                            \
                            \
                            \
    BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_wrapper,std::execution::sequenced_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_seq"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 5, 1 << 5); \
    BENCHMARK_TEMPLATE1(b1_4_for_each_exponential_wrapper,std::execution::parallel_policy)->Name(BENCHMARK_NAME("b1_4_for_each_exponential_par"))->CUSTOM_STATISTICS->RangeMultiplier(2)->Range(1 << 2, 1 << 5); \


#endif //MASTER_BENCHMARKS_B1_GROUP_H
