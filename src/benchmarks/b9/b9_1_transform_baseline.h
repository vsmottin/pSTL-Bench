
#ifndef MASTER_BENCHMARKS_B9_1_TRANSFORM_BASELINE_H
#define MASTER_BENCHMARKS_B9_1_TRANSFORM_BASELINE_H

#include <vector>
#include <algorithm>

namespace B9 {

    template<class ExecutionPolicy>
    inline void
    b9_1_transform_baseline(ExecutionPolicy &&policy,
                            const std::vector<int> &input_data,
                            std::vector<int> &res) {

        std::transform(policy, input_data.begin(), input_data.end(), res.begin(), [](const auto &val) {
            return val + 10;
        });

    }

}

#endif //MASTER_BENCHMARKS_B9_1_TRANSFORM_BASELINE_H
