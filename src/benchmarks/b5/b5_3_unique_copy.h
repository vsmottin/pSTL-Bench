
#ifndef MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
#define MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H

#include <algorithm>
#include <vector>
#include <cmath>

template<class ExecutionPolicy>
inline void b5_3_unique_copy_default(ExecutionPolicy &&policy, std::vector<int> &container, std::vector<int> &result) {

    std::unique_copy(policy, container.begin(), container.end(), result.begin());
}

template<class ExecutionPolicy>
inline void b5_3_unique_copy_odd(ExecutionPolicy &&policy, std::vector<int> &container, std::vector<int> &result) {

    std::unique_copy(policy, container.begin(), container.end(), result.begin(), [](const int &v1, const int &v2) {
        return v1 == v2 - 1;
    });
}

#endif //MASTER_BENCHMARKS_B5_3_UNIQUE_COPY_H
