
#ifndef MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <ranges>

namespace B7 {

    //region copy

    /**
     * Result must have enough space to store the copied elements
     */
    template<class ExecutionPolicy, class T>
    inline void
    b7_1_copy(ExecutionPolicy policy,
              const suite::vec<T, ExecutionPolicy> &container,
              suite::vec<T, ExecutionPolicy> &result) {

        std::copy(policy, container.begin(), container.end(), result.begin());
    }

    //endregion copy_if

    //region custom

    /**
     * Result must have enough space to store the copied elements
     */
    template<class ExecutionPolicy, typename View>
    inline void
    b7_1_custom_copy_with_foreach(ExecutionPolicy &&policy,
                                  const std::vector<int> &container,
                                  const View &view,
                                  std::vector<int> &result) {

        std::for_each(policy, view.begin(), view.end(), [&](const auto &index) {
            result[index] = container[index];
        });

    }

    //endregion custom

}

#endif //MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H
