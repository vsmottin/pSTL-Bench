#ifndef MASTER_BENCHMARKS_B1_3_FOR_EACH_EXPONENTIAL_H
#define MASTER_BENCHMARKS_B1_3_FOR_EACH_EXPONENTIAL_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <iostream>
#include <benchmark/benchmark.h>

//TODO: does it make sense to have such a benchmark??
namespace B1 {

    template<class ExecutionPolicy>
    struct FIB {

        ExecutionPolicy m_policy;

        explicit FIB(ExecutionPolicy &policy) : m_policy(policy) {}

        void operator()(const int &index) {
            if (index <= 0) {
                return;
            }

            benchmark::DoNotOptimize(std::tan(index) + std::cos(index));

            std::vector<int> next{index - 1, index - 2};
            std::for_each(m_policy, next.begin(), next.end(), FIB{m_policy});
        }
    };

    template<class ExecutionPolicy, typename T>
    inline void b1_3_for_each_exponential(ExecutionPolicy &policy, const T &input_data) {

        std::for_each(policy, input_data.begin(), input_data.end(), FIB{policy});

    }
    
}

#endif //MASTER_BENCHMARKS_B1_3_FOR_EACH_EXPONENTIAL_H
