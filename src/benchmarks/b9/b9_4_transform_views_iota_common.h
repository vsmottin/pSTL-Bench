
#ifndef MASTER_BENCHMARKS_B9_4_TRANSFORM_VIEWS_IOTA_COMMON_H
#define MASTER_BENCHMARKS_B9_4_TRANSFORM_VIEWS_IOTA_COMMON_H

#include <vector>
#include <algorithm>
#include <ranges>

namespace B9 {

    template<class ExecutionPolicy>
    inline void
    b9_4_transform_views_iota_common(ExecutionPolicy &&policy,
                                     const std::vector<int> &input_data,
                                     std::vector<int> &res) {

        const auto &view = std::views::iota(0, static_cast<int>(input_data.size())) | std::views::common;

        std::transform(policy, view.begin(), view.end(), res.begin(), [&](const auto &index) {
            return input_data[index] + 10;
        });

    }

}

#endif //MASTER_BENCHMARKS_B9_4_TRANSFORM_VIEWS_IOTA_COMMON_H
