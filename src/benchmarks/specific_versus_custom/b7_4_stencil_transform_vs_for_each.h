
#ifndef MASTER_BENCHMARKS_B7_4_STENCIL_TRANSFORM_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_4_STENCIL_TRANSFORM_VS_FOR_EACH_H

#include <algorithm>
#include <functional>
#include <string>
#include <ranges>
#include <cmath>

#include <benchmark_utils.h>

namespace B7 {


    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename View
    >
    inline void
    b7_4_stencil_transform_number_to_neightbours_stdev(ExecutionPolicy &&policy,
                                                       const suite::int_vec<BASE_POLICY> &input_data,
                                                       const View &view,
                                                       suite::double_vec<BASE_POLICY> &result) {


        std::transform(policy, view.begin(), view.end() - 2, result.begin(), [&](const auto &index) {

            constexpr auto nr_of_observation = 3;
            const auto sum = input_data[index] + input_data[index + 1] + input_data[index + 2];

            const auto sampleMean = sum / nr_of_observation;

            auto big_sum = std::pow(input_data[index] - sampleMean, 2);
            big_sum += std::pow(input_data[index + 1] - sampleMean, 2);
            big_sum += std::pow(input_data[index + 2] - sampleMean, 2);

            return std::sqrt(1 / (nr_of_observation - 1) * big_sum);
        });
    }

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename View
    >
    inline void
    b7_4_stencil_for_each_to_neightbours_stdev(ExecutionPolicy &&policy,
                                               const suite::int_vec<BASE_POLICY> &input_data,
                                               const View &view,
                                               suite::double_vec<BASE_POLICY> &result) {

        std::for_each(policy, view.begin(), view.end() - 2, [&](const auto &index) {

            constexpr auto nr_of_observation = 3;
            const auto sum = input_data[index] + input_data[index + 1] + input_data[index + 2];

            const auto sampleMean = sum / nr_of_observation;

            auto big_sum = std::pow(input_data[index] - sampleMean, 2);
            big_sum += std::pow(input_data[index + 1] - sampleMean, 2);
            big_sum += std::pow(input_data[index + 2] - sampleMean, 2);

            result[index] = std::sqrt(1 / (nr_of_observation - 1) * big_sum);
        });
    }

}

#endif //MASTER_BENCHMARKS_B7_4_STENCIL_TRANSFORM_VS_FOR_EACH_H
