
#ifndef MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H

#include <algorithm>
#include <vector>

namespace B7 {

    template<class ExecutionPolicy>
    inline void
    b7_4_scalar_transform_number(ExecutionPolicy &&policy,
                                 const std::vector<int> &input_data,
                                 std::vector<int> &result) {

        std::transform(policy, input_data.begin(), input_data.end(), result.begin(), [&](const auto &val) {
            return val * 3 + 10;
        });
    }

    template<class ExecutionPolicy, typename View>
    inline void
    b7_4_scalar_for_each(ExecutionPolicy &&policy,
                         const std::vector<int> &input_data,
                         const View &view,
                         std::vector<int> &result) {

        std::for_each(policy, view.begin(), view.end(), [&](const auto &index) {
            result[index] = input_data[index] * 3 + 10;
        });
    }

}

#endif //MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H
