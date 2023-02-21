
#ifndef MASTER_BENCHMARKS_B5_2_PARTITION_H
#define MASTER_BENCHMARKS_B5_2_PARTITION_H

#include <algorithm>
#include <vector>
#include <cmath>

template<class ExecutionPolicy>
inline std::vector<int>::const_iterator b5_2_partition(ExecutionPolicy &&policy, std::vector<int> &container) {

    return std::partition(policy, container.begin(), container.end(), [](const auto &a) {
        const auto b = a + 2;
        const auto c = M_PI;

        const auto a_squared = std::pow(a, 2);
        const auto b_squared = std::pow(b, 2);
        const auto c_squared = std::pow(c, 2);

        return a_squared == ((int) b_squared + c_squared - 2 * b * c * std::cos(a));
    });
}

#endif //MASTER_BENCHMARKS_B5_2_PARTITION_H
