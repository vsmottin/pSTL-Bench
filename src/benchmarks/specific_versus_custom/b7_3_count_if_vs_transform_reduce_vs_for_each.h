
#ifndef MASTER_BENCHMARKS_B7_3_COUNT_IF_VS_TRANSFORM_REDUCE_VS_FOR_EACH_H
#define MASTER_BENCHMARKS_B7_3_COUNT_IF_VS_TRANSFORM_REDUCE_VS_FOR_EACH_H

#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>

#include <benchmark_utils.h>

namespace B7 {

    struct Orders {
        int price;
        int quantity;
    };

    template<class ExecutionPolicy,
            typename Container,
            typename Diff_Type = typename Container::difference_type,
            typename Reference_Type = typename Container::reference,
            typename Pred = typename std::function<bool>(Reference_Type)
    >
    inline Diff_Type
    b7_3_count_if(ExecutionPolicy &&policy, const Container &container, Pred &&pred) {
        return std::count_if(policy, container.begin(), container.end(), pred);
    }

    template<class ExecutionPolicy,
            typename Container,
            typename Diff_Type = typename Container::difference_type,
            typename Reference_Type = typename Container::reference,
            typename Pred = typename std::function<bool>(Reference_Type)
    >
    inline Diff_Type
    b7_3_custom_count_if_with_transform_reduce(ExecutionPolicy &&policy, const Container &container, Pred &&pred) {
        // the trick is that false = 0 and true = 1
        return std::transform_reduce(policy, container.begin(), container.end(), 0, std::plus(), pred);
    }

    template<class ExecutionPolicy,
            typename Container,
            typename Diff_Type = typename Container::difference_type,
            typename Reference_Type = typename Container::reference,
            typename Pred = typename std::function<bool>(Reference_Type)
    >
    inline Diff_Type
    b7_3_custom_count_if_with_for_each(ExecutionPolicy &&policy, const Container &container, Pred &&pred) {
        std::atomic<Diff_Type> count{0};

        std::for_each(policy, container.begin(), container.end(), [&](const auto &val) {
            if (pred(val)) {
                count++;
            }
        });

        return count.load();
    }
}

#endif //MASTER_BENCHMARKS_B7_3_COUNT_IF_VS_TRANSFORM_REDUCE_VS_FOR_EACH_H
