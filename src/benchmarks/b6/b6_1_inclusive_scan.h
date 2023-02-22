
#ifndef MASTER_BENCHMARKS_B6_1_INCLUSIVE_SCAN_H
#define MASTER_BENCHMARKS_B6_1_INCLUSIVE_SCAN_H

#include <numeric>
#include <vector>
#include <utility>

template<class ExecutionPolicy>
inline std::vector<int>
b6_1_inclusive_scan(ExecutionPolicy &&policy, const std::vector<int> &container) {

    std::vector<int> result(container.size());

    std::inclusive_scan(policy, container.begin(), container.end(), result.begin());

    return result;
}

#endif //MASTER_BENCHMARKS_B6_1_INCLUSIVE_SCAN_H
