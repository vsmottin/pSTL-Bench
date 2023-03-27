
#ifndef MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H
#define MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H

#include <numeric>
#include <vector>
#include <utility>

namespace B6 {

    template<class ExecutionPolicy>
    inline void
    b6_2_exclusive_scan(ExecutionPolicy &&policy, const std::vector<int> &container, std::vector<int> &result) {
        std::exclusive_scan(policy, container.begin(), container.end(), result.begin(), 0);
    }

}

#endif //MASTER_BENCHMARKS_B6_2_EXCLUSIVE_SCAN_H
