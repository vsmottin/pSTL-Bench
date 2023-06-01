
#ifndef PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H
#define PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H

#include <vector>
#include <algorithm>
#include <benchmark_utils.h>

namespace B9 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>
    >
    inline void
    b9_1_transform_baseline(ExecutionPolicy &&policy,
                            const suite::int_vec<BASE_POLICY> &input_data,
                            suite::int_vec<BASE_POLICY> &res) {

        std::transform(policy, input_data.begin(), input_data.end(), res.begin(), [](const auto &val) {
            return val + 10;
        });

    }

}

#endif //PSTL_BENCH_B9_1_TRANSFORM_BASELINE_H
