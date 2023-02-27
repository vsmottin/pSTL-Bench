#ifndef MASTER_BENCHMARKS_B1_3_FOR_EACH_QUADRATIC_SINGLE_LOOP_H
#define MASTER_BENCHMARKS_B1_3_FOR_EACH_QUADRATIC_SINGLE_LOOP_H

#include <benchmark/benchmark.h>

#include <vector>
#include <cmath>
#include <algorithm>
#include <ranges>


namespace B1 {

    template<class OuterExecutionPolicy>
    inline void
    b1_3_for_each_quadratic_single_loop(OuterExecutionPolicy &&outerExecutionPolicy,
                                        const std::vector<int> &input_data) {

        // the idea is to calc the indices rather than have nested execution policies
        const auto data_size = input_data.size();
        const auto index_view = std::views::iota(0, static_cast<int>(data_size * data_size));

        // quite straight forward std::for_each. The body of the lambda has no intention behind it, the goal was just
        // to have a big enough computation that takes some amount of time.
        std::for_each(outerExecutionPolicy, index_view.begin(), index_view.end(), [&](const auto &index) {
            const auto v1_index = index / data_size;
            const auto v2_index = index % data_size;

            benchmark::DoNotOptimize(std::tan(input_data[v1_index]) + std::cos(input_data[v2_index]));
        });

    }
}

#endif //MASTER_BENCHMARKS_B1_3_FOR_EACH_QUADRATIC_SINGLE_LOOP_H
