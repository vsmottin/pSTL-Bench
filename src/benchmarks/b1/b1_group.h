#ifndef MASTER_BENCHMARKS_B1_GROUP_H
#define MASTER_BENCHMARKS_B1_GROUP_H

#include <execution>
#include <benchmark/benchmark.h>
#include "b1_1_for_each_linear.h"
#include "b1_2_for_each_quadratic.h"

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


// Register the function as a benchmark
#define B1_GROUP_BENCHMARKS \
                            \
    BENCHMARK(b1_1_for_each_linear_seq)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par_unseq)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
                             \
                             \
    BENCHMARK(b1_2_for_each_quadratic_seq)->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \
    BENCHMARK(b1_2_for_each_quadratic_par)->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \
    BENCHMARK(b1_2_for_each_quadratic_par_unseq)->RangeMultiplier(2)->Range(1 << 5, 1 << 15); \

#endif //MASTER_BENCHMARKS_B1_GROUP_H
