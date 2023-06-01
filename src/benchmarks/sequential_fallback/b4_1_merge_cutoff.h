
#ifndef PSTL_BENCH_B4_1_MERGE_CUTOFF_H
#define PSTL_BENCH_B4_1_MERGE_CUTOFF_H

#include <algorithm>
#include <vector>
#include <benchmark_utils.h>

namespace B4 {

    template<class ExecutionPolicy,
            typename base_policy = typename suite::base_type<ExecutionPolicy>>
    inline void
    b4_1_merge_cutoff(ExecutionPolicy &&policy,
                      const suite::int_vec<base_policy> &v1,
                      const suite::int_vec<base_policy> &v2,
                      suite::int_vec<base_policy> &result) {
        std::merge(policy, v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
    }

}


#endif //PSTL_BENCH_B4_1_MERGE_CUTOFF_H
