
#ifndef MASTER_BENCHMARKS_B7_6_SERIAL_TRANSFORM_REDUCE_VS_TRANSFORM_REDUCE_H
#define MASTER_BENCHMARKS_B7_6_SERIAL_TRANSFORM_REDUCE_VS_TRANSFORM_REDUCE_H

#include <algorithm>
#include <vector>
#include <numeric>
#include <functional>

namespace B7 {

    struct Pixel {
        int red;
        int green;
        int blue;

        [[nodiscard]] inline int sum() const {
            return this->red + this->blue + this->green;
        }
    };

    template<typename Policy>
    using PIXEL_VEC = suite::vec<Pixel, Policy>;


    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>>
    inline int
    b7_6_serial_transform_reduce(ExecutionPolicy &&policy,
                                 const PIXEL_VEC<BASE_POLICY> &input_data) {

        std::vector<int> result(input_data.size());

        std::transform(policy, input_data.begin(), input_data.end(), result.begin(), [&](const auto &val) {
            return val.sum();
        });

        return std::reduce(policy, result.begin(), result.end(), 0, std::plus());
    }


    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>>
    inline int
    b7_6_transform_reduce(ExecutionPolicy &&policy,
                          const PIXEL_VEC<BASE_POLICY> &input_data) {
        return std::transform_reduce(policy, input_data.begin(), input_data.end(), 0, std::plus(),
                                     [&](const auto &val) {
                                         return val.sum();
                                     });
    }

}
#endif //MASTER_BENCHMARKS_B7_6_SERIAL_TRANSFORM_REDUCE_VS_TRANSFORM_REDUCE_H
