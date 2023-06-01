
#ifndef MASTER_BENCHMARKS_B4_3_SET_UNION_CUTOFF_H
#define MASTER_BENCHMARKS_B4_3_SET_UNION_CUTOFF_H

#include <algorithm>
#include <vector>
#include <benchmark_utils.h>

namespace B4 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>>
    inline void
    b4_3_set_union_cutoff(ExecutionPolicy &&policy,
                          const suite::int_vec<BASE_POLICY> &v1,
                          const suite::int_vec<BASE_POLICY> &v2,
                          suite::int_vec<BASE_POLICY> &result) {
        std::set_union(policy, v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
    }

}

#endif //MASTER_BENCHMARKS_B4_3_SET_UNION_CUTOFF_H
