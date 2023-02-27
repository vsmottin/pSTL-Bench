
#ifndef MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_LARGE_OBJECT_H
#define MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_LARGE_OBJECT_H

#include <vector>
#include <algorithm>

namespace B8 {

    struct alignas(512) LargeObject {
        int nr_1;
        int nr_2;
        int nr_3;

        [[nodiscard]] int sum() const {
            return this->nr_1 + this->nr_2 + this->nr_3;
        }
    };

    template<class ExecutionPolicy>
    inline bool
    b8_2_lambda_reference_capture_object_var(ExecutionPolicy &&policy,
                                             std::vector<int> &input_data,
                                             const LargeObject &obj) {

        return std::all_of(policy, input_data.begin(), input_data.end(), [&obj](const auto &val) {
            return val <= obj.sum();
        });

    }

    template<class ExecutionPolicy>
    inline bool
    b8_2_lambda_copy_capture_object_var(ExecutionPolicy &&policy,
                                        std::vector<int> &input_data,
                                        const LargeObject &obj) {

        return std::all_of(policy, input_data.begin(), input_data.end(), [=](const auto &val) {
            return val <= obj.sum();
        });

    }

}

#endif //MASTER_BENCHMARKS_B8_1_REFERENCE_VS_COPY_LARGE_OBJECT_H
