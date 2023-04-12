
#ifndef MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
#define MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H

#include <algorithm>
#include <vector>
#include <cmath>


namespace B5 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>>
    inline void
    b5_3_unique_copy_default(ExecutionPolicy &&policy,
                             suite::int_vec<BASE_POLICY> &container,
                             suite::int_vec<BASE_POLICY> &result) {

        std::unique_copy(policy, container.begin(), container.end(), result.begin());
    }

}

#endif //MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
