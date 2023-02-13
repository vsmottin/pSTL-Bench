#ifndef MASTER_BENCHMARKS_B1_GROUP_H
#define MASTER_BENCHMARKS_B1_GROUP_H

#include <execution>
#include <ranges>
#include <benchmark/benchmark.h>
#include "b1_1_for_each_linear.h"
#include "b1_2_for_each_quadratic.h"
#include "b1_3_for_each_exponential.h"
#include "../benchmark_prefix.h"

//region b1_1_for_each_linear

static void b1_1_for_each_linear_seq(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_1_for_each_linear(std::execution::seq, x);
    }
}

static void b1_1_for_each_linear_par(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_1_for_each_linear(std::execution::par, x);
    }
}

static void b1_1_for_each_linear_par_unseq(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_1_for_each_linear(std::execution::par_unseq, x);
    }
}

//endregion b1_1_for_each_linear


//region b1_2_for_each_quadratic

static void b1_2_for_each_quadratic_seq(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_2_for_each_quadratic(std::execution::seq, x);
    }
}

static void b1_2_for_each_quadratic_par(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_2_for_each_quadratic(std::execution::par, x);
    }
}

static void b1_2_for_each_quadratic_par_unseq(benchmark::State &state) {

    std::vector<int> x(state.range(0), 1);

    for (auto _: state) {
        b1_2_for_each_quadratic(std::execution::par_unseq, x);
    }
}

//endregion b1_2_for_each_quadratic

//region b1_3_for_each_exponential


static void b1_3_for_each_exponential_seq(benchmark::State &state) {
    const auto &data = std::ranges::iota_view(1, static_cast<int>(state.range(0)));
    for (auto _: state) {
        b1_3_for_each_exponential(std::execution::seq, data);
    }
}

static void b1_3_for_each_exponential_par(benchmark::State &state) {
    const auto &data = std::ranges::iota_view(1, static_cast<int>(state.range(0)));
    for (auto _: state) {
        b1_3_for_each_exponential(std::execution::par, data);
    }
}

static void b1_3_for_each_exponential_par_unseq(benchmark::State &state) {
    const auto &data = std::ranges::iota_view(1, static_cast<int>(state.range(0)));
    for (auto _: state) {
        b1_3_for_each_exponential(std::execution::par_unseq, data);
    }
}


//endregion b1_3_for_each_exponential

// Register the function as a benchmark
#define B1_GROUP_BENCHMARKS \
                            \
                            \
    BENCHMARK(b1_1_for_each_linear_seq)->Name(BENCHMARK_NAME("b1_1_for_each_linear_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par)->Name(BENCHMARK_NAME("b1_1_for_each_linear_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par_unseq)->Name(BENCHMARK_NAME("b1_1_for_each_linear_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                             \
                             \
    BENCHMARK(b1_2_for_each_quadratic_seq)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_seq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \
    BENCHMARK(b1_2_for_each_quadratic_par)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_par"))->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \
    BENCHMARK(b1_2_for_each_quadratic_par_unseq)->Name(BENCHMARK_NAME("b1_2_for_each_quadratic_par_unseq"))->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \
                            \
                            \
    BENCHMARK(b1_3_for_each_exponential_seq)->Name(BENCHMARK_NAME("b1_3_for_each_exponential_seq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 5); \
    BENCHMARK(b1_3_for_each_exponential_par)->Name(BENCHMARK_NAME("b1_3_for_each_exponential_par"))->RangeMultiplier(2)->Range(1 << 2, 1 << 5); \
    BENCHMARK(b1_3_for_each_exponential_par_unseq)->Name(BENCHMARK_NAME("b1_3_for_each_exponential_par_unseq"))->RangeMultiplier(2)->Range(1 << 2, 1 << 5);

#endif //MASTER_BENCHMARKS_B1_GROUP_H
