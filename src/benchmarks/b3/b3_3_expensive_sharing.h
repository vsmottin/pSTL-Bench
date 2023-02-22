
#ifndef MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H
#define MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <benchmark/benchmark.h>


namespace B3 {

    template<class ExecutionPolicy>
    inline std::size_t
    b3_3_expensive_sharing(ExecutionPolicy &policy, const std::vector<int> &input_data) {

        std::atomic<int> toggle{0};

        return std::count_if(policy, input_data.begin(), input_data.end(), [&toggle](const auto &val) {
            toggle++; // simulates an expensive mutex operation that forces us to wait
            return val >= 0;
        });
    }

}

#endif //MASTER_BENCHMARKS_B3_3_EXPENSIVE_SHARING_H
