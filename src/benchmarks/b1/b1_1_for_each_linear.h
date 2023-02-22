#ifndef MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H
#define MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H


#include <vector>
#include <cmath>
#include <algorithm>
#include <benchmark/benchmark.h>

namespace B1 {

    template<class ExecutionPolicy>
    inline void b1_1_for_each_linear(ExecutionPolicy &policy, const std::vector<int> &input_data) {

        // quite straight forward std::for_each. The body of the lambda has no intention behind it, the goal was just
        // to have a big enough computation that takes some amount of time.
        std::for_each(policy, input_data.begin(), input_data.end(), [](const auto &entry) {
            return benchmark::DoNotOptimize(std::min(std::sin(entry), std::tan(entry)));
        });

    }

}

#endif //MASTER_BENCHMARKS_B1_1_FOR_EACH_LINEAR_H
