
#ifndef PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H
#define PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H

#include <numeric>
#include <vector>
#include <utility>
#include <benchmark_utils.h>

namespace B6 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b6_1_inclusive_scan(ExecutionPolicy &&policy,
                        const suite::int_vec<BASE_POLICY> &container,
                        suite::int_vec<BASE_POLICY> &result) {
        std::inclusive_scan(policy, container.begin(), container.end(), result.begin());
    }

}

#endif //PSTL_BENCH_B6_1_INCLUSIVE_SCAN_H
