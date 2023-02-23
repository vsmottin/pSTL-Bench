
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
    template<class ExecutionPolicy>
    inline void
    b7_1_copy(ExecutionPolicy &&policy, const std::vector<int> &container, std::vector<int> &result) {

        std::copy(policy, container.begin(), container.end(), result.begin());
    }

    //endregion copy_if

    //region custom

    /**
     * Result must have enough space to store the copied elements
     */
    template<class ExecutionPolicy>
    inline void
    b7_custom_copy_with_foreach(ExecutionPolicy &&policy, const std::vector<int> &container, std::vector<int> &result) {

        const auto &view = std::views::iota(0, static_cast<int>(container.size()));

        std::for_each(policy, view.begin(), view.end(), [&](const auto &index) {
            result[index] = container[index];
        });

    }

    //endregion custom

}

#endif //MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H
