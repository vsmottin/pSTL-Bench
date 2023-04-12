
#ifndef MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H

#include <algorithm>
#include <vector>

namespace B7 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b7_5_scalar_transform_number(ExecutionPolicy &&policy,
                                 const suite::int_vec<BASE_POLICY> &input_data,
                                 suite::int_vec<BASE_POLICY> &result) {

        std::transform(policy, input_data.begin(), input_data.end(), result.begin(), [&](const auto &val) {
            return val * 3 + 10;
        });
    }

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename View
    >
    inline void
    b7_5_scalar_for_each(ExecutionPolicy &&policy,
                         const suite::int_vec<BASE_POLICY> &input_data,
                         const View &view,
                         suite::int_vec<BASE_POLICY> &result) {

        std::for_each(policy, view.begin(), view.end(), [&](const auto &index) {
            result[index] = input_data[index] * 3 + 10;
        });
    }

}

#endif //MASTER_BENCHMARKS_B7_5_SCALAR_TRANSFORM_VS_FOR_EACH_H
