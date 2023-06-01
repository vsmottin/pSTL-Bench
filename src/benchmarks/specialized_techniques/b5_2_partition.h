
#ifndef PSTL_BENCH_B5_2_PARTITION_H
#define PSTL_BENCH_B5_2_PARTITION_H

#include <algorithm>
#include <vector>
#include <cmath>
#include <benchmark_utils.h>

namespace B5 {

    template<class ExecutionPolicy,
            typename BASE_POLICY = typename suite::base_type<ExecutionPolicy>>
    inline suite::int_vec<BASE_POLICY>::const_iterator
    b5_2_partition(ExecutionPolicy &&policy, suite::int_vec<BASE_POLICY> &container) {

        return std::partition(policy, container.begin(), container.end(), [](const auto &a) {
            const auto b = a + 2;
            const auto c = M_PI;

            const auto a_squared = std::pow(a, 2);
            const auto b_squared = std::pow(b, 2);
            const auto c_squared = std::pow(c, 2);

            return a_squared == ((int) b_squared + c_squared - 2 * b * c * std::cos(a));
        });
    }

}

#endif //PSTL_BENCH_B5_2_PARTITION_H
