#ifndef MASTER_BENCHMARKS_B1_2_FOR_EACH_QUADRATIC_H
#define MASTER_BENCHMARKS_B1_2_FOR_EACH_QUADRATIC_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <benchmark/benchmark.h>


namespace B1 {

    template<class OuterExecutionPolicy, class InnerExecutionPolicy, typename T>
    inline void
    b1_2_for_each_quadratic(OuterExecutionPolicy outerExecutionPolicy,
                            InnerExecutionPolicy innerExecutionPolicy,
                            const T &input_data) {

        // quite straight forward std::for_each. The body of the lambda has no intention behind it, the goal was just
        // to have a big enough computation that takes some amount of time.
        std::for_each(outerExecutionPolicy, input_data.begin(), input_data.end(), [&](const auto &e1) {

            // nested parallel loop with same strategy
            std::for_each(innerExecutionPolicy, input_data.begin(), input_data.end(), [&e1](const auto &e2) {
                auto value = std::tan(e1) + std::cos(e2);
                benchmark::DoNotOptimize(value);
            });

        });

    }
}

#endif //MASTER_BENCHMARKS_B1_2_FOR_EACH_QUADRATIC_H
