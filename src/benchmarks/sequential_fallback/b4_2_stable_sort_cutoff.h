
#ifndef PSTL_BENCH_B4_2_STABLE_SORT_CUTOFF_H
#define PSTL_BENCH_B4_2_STABLE_SORT_CUTOFF_H

#include <algorithm>
#include <vector>
#include <benchmark_utils.h>

namespace B4 {

    template<class ExecutionPolicy,
            typename base_policy = typename suite::base_type<ExecutionPolicy>>
    inline void
    b4_2_stable_sort_cutoff(ExecutionPolicy &&policy, suite::int_vec<base_policy> &input_data) {

        std::stable_sort(policy, input_data.begin(), input_data.end());

    }

}

#endif //PSTL_BENCH_B4_2_STABLE_SORT_CUTOFF_H
