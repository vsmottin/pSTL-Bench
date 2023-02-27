
#ifndef MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_H
#define MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_H

#include <vector>
#include <algorithm>

namespace B8 {

    template<class ExecutionPolicy>
    inline bool
    b8_1_lambda_reference_capture_simple_var(ExecutionPolicy &&policy,
                                             std::vector<int> &input_data,
                                             const int &magic_number) {

        return std::all_of(policy, input_data.begin(), input_data.end(), [&magic_number](const auto &val) {
            return val <= magic_number;
        });

    }

    template<class ExecutionPolicy>
    inline bool
    b8_1_lambda_copy_capture_simple_var(ExecutionPolicy &&policy,
                                        std::vector<int> &input_data,
                                        const int &magic_number) {

        return std::all_of(policy, input_data.begin(), input_data.end(), [=](const auto &val) {
            return val <= magic_number;
        });

    }

}

#endif //MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_H
