#ifndef MASTER_BENCHMARKS_B1_GROUP_H
#define MASTER_BENCHMARKS_B1_GROUP_H

#include <benchmark/benchmark.h>
#include "b1_1_for_each_linear.h"
#include <execution>

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

// Register the function as a benchmark
#define B1_GROUP_BENCHMARKS  \
    BENCHMARK(b1_1_for_each_linear_seq)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \
    BENCHMARK(b1_1_for_each_linear_par_unseq)->RangeMultiplier(2)->Range(1 << 5, 1 << 20); \


#endif //MASTER_BENCHMARKS_B1_GROUP_H
