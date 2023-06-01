
#ifndef MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H
#define MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H

#include <numeric>
#include <vector>
#include <utility>
#include <benchmark_utils.h>

namespace B6 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b6_2_exclusive_scan(ExecutionPolicy &&policy,
                        const suite::int_vec<BASE_POLICY> &container,
                        suite::int_vec<BASE_POLICY> &result) {
        std::exclusive_scan(policy, container.begin(), container.end(), result.begin(), 0);
    }

}

#endif //MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H
