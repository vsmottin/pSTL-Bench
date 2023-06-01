
#ifndef MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H

#include <vector>
#include <algorithm>
#include <functional>
#include <ranges>

#include <benchmark_utils.h>

namespace B7 {

    //region copy

    /**
     * Result must have enough space to store the copied elements
     */
    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename T
    >
    inline void
    b7_1_copy(ExecutionPolicy &&policy,
              const suite::vec<T, BASE_POLICY> &container,
              suite::vec<T, BASE_POLICY> &result) {

        std::copy(policy, container.begin(), container.end(), result.begin());
    }

    //endregion copy_if

    //region custom

    /**
     * Result must have enough space to store the copied elements
     */
    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>,
            typename View
    >
    inline void
    b7_1_custom_copy_with_foreach(ExecutionPolicy &&policy,
                                  const suite::int_vec<BASE_POLICY> &container,
                                  const View &view,
                                  suite::int_vec<BASE_POLICY> &result) {

        std::for_each(policy, view.begin(), view.end(), [&](const auto &index) {
            result[index] = container[index];
        });

    }

    //endregion custom

}

#endif //MASTER_BENCHMARKS_B7_1_COPY_VS_FOR_EACH_H
