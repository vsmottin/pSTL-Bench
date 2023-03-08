
#ifndef MASTER_BENCHMARKS_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H
#define MASTER_BENCHMARKS_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

namespace B7 {

    template<class ExecutionPolicy,
            typename Pred = typename std::function<bool>(std::vector<int>::const_reference)
    >
    inline bool
    b7_2_all_of(ExecutionPolicy &&policy, const std::vector<int> &container, Pred &&pred) {

        return std::all_of(policy, container.begin(), container.end(), pred);
    }


    template<class ExecutionPolicy,
            typename Pred = typename std::function<bool>(std::vector<int>::const_reference)
    >
    inline bool
    b7_2_custom_all_of_with_transform_reduce(ExecutionPolicy &&policy, const std::vector<int> &container, Pred &&pred) {

        return std::transform_reduce(policy, container.begin(), container.end(), true, std::logical_and(), pred);
    }

}

#endif //MASTER_BENCHMARKS_B7_2_ALL_OFF_VS_TRANSFORM_REDUCE_H
